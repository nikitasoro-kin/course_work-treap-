#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include "treap.h"

class TreeWidget : public QWidget {
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    void setTreap(Treap* treap);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Treap* treap;
    int nodeRadius = 22;
    int verticalSpacing = 60;

    void calculatePositions(QPainter& painter, TreapNode* node, int x, int y, int level);
    int calculateSubtreeWidth(TreapNode* node);
};

#endif // TREEWIDGET_H
