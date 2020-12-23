#include "switchcontrol.h"

#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QSize>

using namespace Mtr;

SwitchControl::SwitchControl(QWidget *parent) : QWidget(parent)
{
    mTimeline.setDuration(240);
    mTimeline.setEasingCurve(QEasingCurve::InSine);
    connect(&mTimeline, &QTimeLine::frameChanged, this, &SwitchControl::slot_current_frame_change);
}

void SwitchControl::SwitchOn()
{
    if (mTimeline.state() == QTimeLine::Running) return;
    mTimeline.setFrameRange(0, 100);
    mTimeline.start();
}

void SwitchControl::SwitchOff()
{
    if (mTimeline.state() == QTimeLine::Running) return;
    mTimeline.setFrameRange(100, 0);
    mTimeline.start();
}

bool SwitchControl::isSwitchOn()
{
    return mTimeline.currentFrame() == 100;
}

void SwitchControl::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(1);
    pen.setColor(QColor(mBorderColor));
    painter.setPen(pen);

    float width = this->width();
    float height = this->height();

    int frame = mTimeline.currentFrame();

    QPainterPath path;
    float radiusBackground = (height - 8) * 0.5;
    path.addRoundedRect(QRectF(4, 4, width - 8, height - 8), radiusBackground, radiusBackground);
    painter.fillPath(path, (frame < 50) ? QBrush(QColor(mBackgroundOffColor)) : QBrush(QColor(mBackgroundOnColor)));
    painter.drawRoundedRect(QRectF(4, 4, width - 8, height - 8), radiusBackground, radiusBackground);

    QPainterPath dotPath;
    float radiusDot = (height - 14) * 0.5;
    float max = (width - height * 2);
    float add = frame == 100 ? 0 : (frame > 50) ? (100 - frame) / 50.0 * max : frame / 50.0 * max;
    add = add < 0 ? 0 : add;
    dotPath.addRoundedRect(QRectF(7 + (frame / 100.00) * (width - height), 7, (height - 14) + add, height - 14), radiusDot, radiusDot);
    painter.fillPath(dotPath, QBrush(QColor(mDotColor)));

    event->accept();
}

void SwitchControl::enterEvent(QEvent *event)
{
    mEntered = true;
    event->accept();
}

void SwitchControl::leaveEvent(QEvent *event)
{
    mEntered = false;
    event->accept();
}

void SwitchControl::mousePressEvent(QMouseEvent *event)
{
    mPressed = true;
    if (event->button() != Qt::LeftButton) return;
    event->accept();
}

void SwitchControl::mouseReleaseEvent(QMouseEvent *event)
{
    if (!mEntered || !mPressed) return;
    mPressed = false;
    event->accept();
    if (mTimeline.state() == QTimeLine::Running) return;
    if (mTimeline.currentFrame() == 100) mTimeline.setFrameRange(100, 0);
    else mTimeline.setFrameRange(0, 100);
    mTimeline.start();
}

void SwitchControl::resizeEvent(QResizeEvent *event)
{
    setMinimumHeight(48);
    setMinimumWidth(height() * 2.2);
    event->accept();
}

void SwitchControl::slot_current_frame_change(int frame)
{
    Q_UNUSED(frame);
    update();
}

QString SwitchControl::getBorderColor() const
{
    return mBorderColor;
}

void SwitchControl::setBorderColor(const QString &borderColor)
{
    mBorderColor = borderColor;
}

QString SwitchControl::getDotColor() const
{
    return mDotColor;
}

void SwitchControl::setDotColor(const QString &dotColor)
{
    mDotColor = dotColor;
}

QString SwitchControl::getBackgroundOffColor() const
{
    return mBackgroundOffColor;
}

void SwitchControl::setBackgroundOffColor(const QString &backgroundOffColor)
{
    mBackgroundOffColor = backgroundOffColor;
}

QString SwitchControl::getBackgroundOnColor() const
{
    return mBackgroundOnColor;
}

void SwitchControl::setBackgroundOnColor(const QString &backgroundOnColor)
{
    mBackgroundOnColor = backgroundOnColor;
}
