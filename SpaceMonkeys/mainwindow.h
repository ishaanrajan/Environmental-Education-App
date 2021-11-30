#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <box2d/box2d.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected slots:
    void onAdd();
    void onRemove();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QListView* category1View = nullptr;
    QListView* category2View = nullptr;

    QAction* addAction = nullptr;
    QAction* removeAction = nullptr;
};
#endif // MAINWINDOW_H
