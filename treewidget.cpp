#include "treewidget.h"
#include <QPainter>
#include <cmath>

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), treap(nullptr) {}

void TreeWidget::setTreap(Treap* t) {
    treap = t;
    update();
    updateGeometry();
}

int TreeWidget::calculateTreeHeight(TreapNode* node) const {
    if (!node) return 0;
    return 1 + std::max(calculateTreeHeight(node->left),
                        calculateTreeHeight(node->right));
}

QSize TreeWidget::minimumSizeHint() const {
    if (!treap || !treap->getRoot()) {
        return QSize(100, 100); 
    }

    int width = calculateSubtreeWidth(treap->getRoot()) * nodeRadius * 4;
    int height = calculateTreeHeight(treap->getRoot()) * verticalSpacing + 100;

    return QSize(width, height);
}

void TreeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    if (treap && treap->getRoot()) {
        int width = calculateSubtreeWidth(treap->getRoot()) * nodeRadius * 4;
        int height = calculateTreeHeight(treap->getRoot()) * verticalSpacing + 100;

        setMinimumSize(width, height);

        int startX = this->width() / 2;
        calculatePositions(painter, treap->getRoot(), startX, 50, 0);

        qDebug() << "Tree painted. Size:" << size() << "Min size:" << minimumSize();
    }
}

void TreeWidget::calculatePositions(QPainter& painter, TreapNode* node, int x, int y, int level) {
    if (!node) return;

    int leftWidth = calculateSubtreeWidth(node->left);
    int rightWidth = calculateSubtreeWidth(node->right);

    node->posX = x;
    node->posY = y;

    if (node->left) {
        int childX = x - (rightWidth + 1) * nodeRadius * 2;
        int childY = y + verticalSpacing;
        painter.drawLine(x, y, childX, childY);
        calculatePositions(painter, node->left, childX, childY, level + 1);
    }

    if (node->right) {
        int childX = x + (leftWidth + 1) * nodeRadius * 2;
        int childY = y + verticalSpacing;
        painter.drawLine(x, y, childX, childY);
        calculatePositions(painter, node->right, childX, childY, level + 1);
    }

    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(x, y), nodeRadius, nodeRadius);
    painter.drawText(QRect(x - nodeRadius, y - nodeRadius,
                           nodeRadius * 2, nodeRadius * 2),
                     Qt::AlignCenter, QString::number(node->key) + "/" + QString::number(node->priority));
}

int TreeWidget::calculateSubtreeWidth(TreapNode* node) const {
    if (!node) return 0;
    return 1 + calculateSubtreeWidth(node->left) + calculateSubtreeWidth(node->right);
}

