#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QChar>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void nouveauficher();
    bool PE_Sauve();//Pour montrer le dossier a déjà enregistré ou pas
    bool Sauve();
    bool Sauve_S();// sauvegarde sous
    bool Sauve_ficher(const QString &fileName);//Pour enregistrer le dossier avec nom de dossier en argument
    bool Charger_filche(const QString &fileName);

    QStringList getDirFilesName(QString path);

private slots:
    void on_actioncreate_triggered();

    void on_actionopen_o_triggered();

    void on_actionsave_s_triggered();

    void on_actionSauvegarder_Sous_a_triggered();

    void on_actionclose_c_triggered();

    void on_actionAnuler_z_triggered();

    void on_actionCouper_x_triggered();

    void on_actionCopier_v_triggered();

    void on_actionPaster_triggered();

    void on_actionSupprimer_d_triggered();

    void on_teste_clicked();

    void on_ouv_clicked();

private:
    Ui::MainWindow *ui;
    bool utile;//La variable qui permet de montrer le dossier est en utilisant ou pas
    QString parcour;// Permet de récupérer le parcours du dossier
};
#endif // MAINWINDOW_H
