#ifndef ADS_H
#define ADS_H

#include <QWidget>
#include <QLabel>

class Ads : public QWidget
{
    Q_OBJECT
public:
    explicit Ads(QWidget *parent = 0);

    void createComponent();

    void input();

    void resizeEvent(QResizeEvent *);

signals:

public slots:


private:


public:
    QLabel  *lTitle;

};

#endif // ADS_H
