#ifndef SWITCHCONTROL_H
#define SWITCHCONTROL_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimeLine>

namespace Mtr {

class SwitchControl : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchControl(QWidget *parent = nullptr);

    void SwitchOn();
    void SwitchOff();

    bool isSwitchOn();

    QString getBackgroundOnColor() const;
    void setBackgroundOnColor(const QString &backgroundOnColor);

    QString getBackgroundOffColor() const;
    void setBackgroundOffColor(const QString &backgroundOffColor);

    QString getDotColor() const;
    void setDotColor(const QString &dotColor);

    QString getBorderColor() const;
    void setBorderColor(const QString &borderColor);

protected:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private slots:
    void slot_current_frame_change(int frame);

private:
    QString mBackgroundOnColor      = "#5BC560";
    QString mBackgroundOffColor     = "#DDDDDD";
    QString mDotColor               = "#FEFEFE";
    QString mBorderColor            = "#CCCCCC";

    QTimeLine mTimeline;

    bool mEntered = false;
    bool mPressed = false;
};

}

#endif // SWITCHCONTROL_H
