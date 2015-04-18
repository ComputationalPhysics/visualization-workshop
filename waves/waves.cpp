#include "diffusion.h"

#include <QPainter>

Diffusion::Diffusion()
{
    reset();
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

Diffusion::~Diffusion()
{

}

void Diffusion::setRowCount(int arg)
{
    if (m_rowCount == arg) {
        return;
    }

    m_rowCount = arg;
    emit rowCountChanged(arg);

    reset();
}

void Diffusion::setColumnCount(int arg)
{
    if (m_columnCount == arg) {
        return;
    }

    m_columnCount = arg;
    emit columnCountChanged(arg);

    reset();
}

void Diffusion::reset()
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

void Diffusion::mousePressEvent(QMouseEvent *event)
{

}

void Diffusion::mouseMoveEvent(QMouseEvent *event)
{
    int j = m_columnCount * event->x() / boundingRect().width();
    int i = m_rowCount * event->y() / boundingRect().height();

    m_values[i][j] = 1.0;
    m_values[i-1][j] = 0.3;
    m_values[i+1][j] = 0.3;
    m_values[i][j-1] = 0.3;
    m_values[i][j+1] = 0.3;

    update();
}

void Diffusion::paint(QPainter *painter)
{
    QImage image(m_columnCount, m_rowCount, QImage::Format_RGBA8888);

    for(int i = 0; i < m_rowCount; i++) {
        for(int j = 0; j < m_columnCount; j++) {
            double value = fmin(fmax(0, m_values[i][j]), 1.0);
            QColor color(value * 255, 0, 0);
            image.setPixel(j, i, color.rgba());
        }
    }

    painter->drawImage(boundingRect(), image);
}

int Diffusion::rowCount() const
{
    return m_rowCount;
}

int Diffusion::columnCount() const
{
    return m_columnCount;
}

void Diffusion::step()
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
                neighborValues += 0.25*m_values[i][left];
            }
            if(right < m_columnCount - 1) {
                neighborValues += 0.25*m_values[i][right];
            }
            if(up > 0) {
                neighborValues += 0.25*m_values[up][j];
            }
            if(down < m_rowCount - 1) {
                neighborValues += 0.25*m_values[down][j];
            }
//            double ratio = 0.01;
            double diff = neighborValues - value;
            double prev = m_valuesPrevious[i][j];
            double timeDiff = value - m_valuesPrevious[i][j];
            m_valuesNext[i][j] = 2 * value - prev + 0.01 * (neighborValues - 4 * value);
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

