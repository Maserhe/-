#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H
#include<QMessageBox>
#include <QObject>
#include <QWidget>

class MymessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit MymessageBox(QWidget *parent = nullptr);

    void showEvent(QShowEvent *event) override;

signals:

public slots:
};

#endif // MYMESSAGEBOX_H
