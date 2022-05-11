#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QStringList>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief exit closes the application
     */
    void exit();

    /**
     * @brief showAbout shows the about dialog.
     */
    void showAbout();

    /**
     * @brief showHistory shows the command history.
     */
    void showHistory();

    /**
     * @brief showWelcome shows the welcome central view.
     */
    void showWelcome();

public slots:
    /**
     * @brief showProcessScheduler shows the view to deal with process scheduling.
     */
    void showProcessScheduler();

private:
    /**
     * @brief setupUi sets up the user interface.
     */
    void setupUi();

    /**
     * @brief setupMenuBar sets up the menu bar.
     */
    void setupMenuBar();

private:
    QStackedWidget* stackedWidget;
    QWidget* welcomeWidget;
    QWidget* processSchedulerWidget;

    QStringList historyList;
};

#endif // MAINWINDOW_H
