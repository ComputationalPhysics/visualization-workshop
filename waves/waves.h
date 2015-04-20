#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <QQuickPaintedItem>

#include <vector>

using namespace std;

class Waves : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double courant READ courant WRITE setCourant NOTIFY courantChanged)
public:
    Waves();
    ~Waves();

    void paint(QPainter *painter);

    int rowCount() const;
    int columnCount() const;
    QColor color() const;
    double courant() const;

signals:
    void rowCountChanged(int arg);
    void columnCountChanged(int arg);
    void colorChanged(QColor arg);
    void courantChanged(double arg);

public slots:
    void setRowCount(int arg);
    void setColumnCount(int arg);
    void setColor(QColor arg);
    void setCourant(double arg);

    void step();

private:
    void reset();

    int m_rowCount = 100;
    int m_columnCount = 100;

    vector<vector<double> > m_values;
    vector<vector<double> > m_valuesNext;
    vector<vector<double> > m_valuesPrevious;

    // QQuickItem interface
    void createWave(double x, double y, double amplitude);
    QColor m_color = QColor(Qt::white);

    double m_courant;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // DIFFUSION_H
