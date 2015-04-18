#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <QQuickPaintedItem>

#include <vector>

using namespace std;

class Diffusion : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
public:
    Diffusion();
    ~Diffusion();

    void paint(QPainter *painter);

    int rowCount() const;
    int columnCount() const;

signals:
    void rowCountChanged(int arg);
    void columnCountChanged(int arg);

public slots:
    void setRowCount(int arg);
    void setColumnCount(int arg);
    void step();

private:
    void reset();

    int m_rowCount = 100;
    int m_columnCount = 100;

    vector<vector<double> > m_values;
    vector<vector<double> > m_valuesNext;
    vector<vector<double> > m_valuesPrevious;

    // QQuickItem interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // DIFFUSION_H
