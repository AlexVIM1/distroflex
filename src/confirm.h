#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>

namespace Ui {
class confirm;
}

class confirm : public QDialog
{
    Q_OBJECT

public:
    bool getResult() const { return itsResult; }
    confirm(QString operation);
    ~confirm();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::confirm *ui;
    bool itsResult;
};

#endif // CONFIRM_H
