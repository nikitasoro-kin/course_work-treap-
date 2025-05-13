#include "treewidget.h"
#include <QPainter>
#include <cmath>

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), treap(nullptr) {}

void TreeWidget::setTreap(Treap* t) {
    treap = t;
    update();
}

void TreeWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (treap && treap->getRoot()) {
        calculatePositions(painter, treap->getRoot(), width()/2, 50, 0);
    }
}

// Рекурсивный расчет позиций узлов
void TreeWidget::calculatePositions(QPainter& painter, TreapNode* node, int x, int y, int level) {
    if (!node) return;

    // Рассчитываем горизонтальный отступ на основе ширины поддеревьев
    int leftWidth = calculateSubtreeWidth(node->left);
    int rightWidth = calculateSubtreeWidth(node->right);

    // Сохраняем позицию узла
    node->posX = x;
    node->posY = y;

    // Рисуем связи с дочерними узлами
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

    // Рисуем узел
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(x, y), nodeRadius, nodeRadius);
    painter.drawText(QRect(x - nodeRadius, y - nodeRadius,
                           nodeRadius * 2, nodeRadius * 2),
                     Qt::AlignCenter, QString::number(node->key) + "/" + QString::number(node->priority));
}

// Расчет ширины поддерева
int TreeWidget::calculateSubtreeWidth(TreapNode* node) {
    if (!node) return 0;
    return 1 + calculateSubtreeWidth(node->left) + calculateSubtreeWidth(node->right);
}
