#include "waves.h"

#include <QPainter>

Waves::Waves()
{
    reset();
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

Waves::~Waves()
{

}

void Waves::setRowCount(int arg)
{
    if (m_rowCount == arg) {
        return;
    }

    m_rowCount = arg;
    emit rowCountChanged(arg);

    reset();
}

void Waves::setColumnCount(int arg)
{
    if (m_columnCount == arg) {
        return;
    }

    m_columnCount = arg;
    emit columnCountChanged(arg);

    reset();
}

void Waves::reset()
{
    m_values.resize(m_rowCount);
    m_valuesNext.resize(m_rowCount);
    m_valuesPrevious.resize(m_rowCount);
    for(int i = 0; i < m_rowCount; i++) {
        m_values[i].resize(m_columnCount);
        m_valuesNext[i].resize(m_columnCount);
        m_valuesPrevious[i].resize(m_columnCount);

        for(int j = 0; j < m_columnCount; j++) {
            m_values[i][j] = 0.0;
            m_valuesNext[i][j] = 0.0;
            m_valuesPrevious[i][j] = 0.0;
        }
    }
}

void Waves::mousePressEvent(QMouseEvent *event)
{
    createWave(event->x(), event->y(), 2.0);
}

void Waves::mouseMoveEvent(QMouseEvent *event)
{
    createWave(event->x(), event->y(), 0.05);
}

void Waves::createWave(double x, double y, double amplitude)
{
    int column = m_columnCount * x / boundingRect().width();
    int row = m_rowCount * y / boundingRect().height();

    for(int i = 0; i < m_rowCount; i++) {
        for(int j = 0; j < m_columnCount; j++) {
            double diffX = column - j;
            double diffY = row - i;
            double distance = sqrt(diffX*diffX + diffY*diffY);
            double factor = 15.0;
            double value = amplitude*exp(-distance*distance/(2.0*factor));
            m_values[i][j] += value;
            m_valuesPrevious[i][j] += value;
        }
    }

    update();
}

void Waves::paint(QPainter *painter)
{
    QImage image(m_columnCount, m_rowCount, QImage::Format_RGBA8888);

    for(int i = 0; i < m_rowCount; i++) {
        for(int j = 0; j < m_columnCount; j++) {
            double value = 0.5 * (1.0 + fmin(fmax(m_values[i][j], -1.0), 1.0));
            QColor color = m_color;
            color.setRed(m_color.red() * value);
            color.setGreen(m_color.green() * value);
            color.setBlue(m_color.blue() * value);
            image.setPixel(j, i, color.rgba());
        }
    }

    painter->drawImage(boundingRect(), image);
}

int Waves::rowCount() const
{
    return m_rowCount;
}

int Waves::columnCount() const
{
    return m_columnCount;
}

QColor Waves::color() const
{
    return m_color;
}

double Waves::courant() const
{
    return m_courant;
}

void Waves::step()
{
    for(int i = 0; i < m_rowCount; i++) {
        for(int j = 0; j < m_columnCount; j++) {
            int left = j - 1;
            int right = j + 1;
            int up = i - 1;
            int down = i + 1;

            double value = m_values[i][j];
            double neighborValues = 0.0;
            if(left > 0) {
                neighborValues += m_values[i][left];
            }
            if(right < m_columnCount - 1) {
                neighborValues += m_values[i][right];
            }
            if(up > 0) {
                neighborValues += m_values[up][j];
            }
            if(down < m_rowCount - 1) {
                neighborValues += m_values[down][j];
            }
            double prev = m_valuesPrevious[i][j];
            double C = m_courant;
            m_valuesNext[i][j] = 2.0 * value - prev + C * (neighborValues - 4 * value);

            // damping
            m_valuesNext[i][j] *= 0.99;
        }
    }

    for(int i = 0; i < m_rowCount; i++) {
        for(int j = 0; j < m_columnCount; j++) {
            m_valuesPrevious[i][j] = m_values[i][j];
            m_values[i][j] = m_valuesNext[i][j];
        }
    }

    update();
}

void Waves::setCourant(double arg)
{
    if (m_courant == arg)
        return;

    m_courant = arg;
    emit courantChanged(arg);
}

void Waves::setColor(QColor arg)
{
    if (m_color == arg)
        return;

    m_color = arg;
    emit colorChanged(arg);
}

