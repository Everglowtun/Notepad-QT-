#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    utile = true;
    parcour = tr("sans_nom.txt");
    setWindowTitle(parcour);
}

QStringList MainWindow::getDirFilesName(QString path)
{
    /*获取文件夹下的文件名称*/
    QDir dir(path);
    //dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList nameFilters;
    nameFilters << "*.txt" ;
    //dir.setNameFilters(filters);
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}
bool MainWindow::Sauve()
{
   if (utile) {
       return Sauve_S();
   } else {
       return Sauve_ficher(parcour);
   }
}
bool MainWindow::Sauve_S()
{
   QString fileName = QFileDialog::getSaveFileName(this,
                                         tr("Sauvegrarder_Sous"),parcour);
   if (fileName.isEmpty()) return false;
   return Sauve_ficher(fileName);
}
bool MainWindow::Sauve_ficher(const QString &fileName)
{
   QFile file(fileName);

   if (!file.open(QFile::WriteOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("éditeur multi-dossiers"),
                   tr("Ne peut pas charger le dossier %1：/n %2")
                  .arg(fileName).arg(file.errorString()));
       return false;
   }
   QTextStream out(&file);
   // Curseur changer au statut d'attend
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->textEdit->toPlainText();
   // Curseur rentrer dans la statut origine
   QApplication::restoreOverrideCursor();
   utile = false;
   // Obtenir le parcours du dossier
   parcour = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(parcour);
   return true;
}
bool MainWindow::PE_Sauve(){
    if(ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("Attention"));
             box.setIcon(QMessageBox::Warning);
             box.setText(parcour + tr(" Pas encore sauvegarder，vous voulez le savegarder？"));
             QPushButton *yesBtn = box.addButton(tr("Oui(&Y)"),
                              QMessageBox::YesRole);
             box.addButton(tr("Non(&N)"), QMessageBox::NoRole);
             QPushButton *cancelBut = box.addButton(tr("Suppirmer"),
                              QMessageBox::RejectRole);
             box.exec();
             if (box.clickedButton() == yesBtn)
                  return Sauve();
             else if (box.clickedButton() == cancelBut)
                  return false;
    }
    return true;
}
void MainWindow::nouveauficher(){
    if(PE_Sauve()){
        utile = true;
        parcour = tr("sans_nom.txt");
        setWindowTitle(parcour);
        ui->textEdit->clear();
    }
}
bool MainWindow::Charger_filche(const QString &fileName)
{
   QFile file(fileName); // créer un nouveau object de qt.
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("éditeur multi-dossiers"),
                             tr("Ne peut pas trouver ce dossier  %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // ouvrir le dossier dans le monde de 'readonly' si il y a erreur returne false
   }
   QTextStream in(&file); // Créer le flux d'objet
   QApplication::setOverrideCursor(Qt::WaitCursor);
   // obtenir tous les contenu de la dossier, copier au éditeur
   ui->textEdit->setPlainText(in.readAll());      QApplication::restoreOverrideCursor();

   // établir le dossier
   parcour = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(parcour);
   return true;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncreate_triggered()
{
    nouveauficher();
}

void MainWindow::on_actionopen_o_triggered()
{
    if (PE_Sauve()) {

           QString fileName = QFileDialog::getOpenFileName(this);

           // Si la nom de dossier n'est pas vide, ouvrir ce dossier
           if (!fileName.isEmpty()) {
                Charger_filche(fileName);
                ui->textEdit->setVisible(true);
           }
       }
}

void MainWindow::on_actionsave_s_triggered()
{
    Sauve();//opération sauvegarder
}


void MainWindow::on_actionSauvegarder_Sous_a_triggered()
{
    Sauve_S();//opération sauvegarder sous
}

void MainWindow::on_actionclose_c_triggered()
{
    if (PE_Sauve()) {
        ui->textEdit->setVisible(false);//opération fermer
    }
}

void MainWindow::on_actionAnuler_z_triggered()
{
    ui->textEdit->undo();//opération annuler
}

void MainWindow::on_actionCouper_x_triggered()
{
    ui->textEdit->cut();//opération couper
}

void MainWindow::on_actionCopier_v_triggered()
{
    ui->textEdit->copy();//opération copier
}

void MainWindow::on_actionPaster_triggered()
{
    ui->textEdit->paste();//opération coller
}

void MainWindow::on_actionSupprimer_d_triggered()
{
    ui->textEdit->clear();//opération de suppression
}

void MainWindow::on_teste_clicked()
{
    //Afficher le list des dossiers concernés
    QString path = ui->lineEdit ->text();
    QStringList sss;
    sss = getDirFilesName(path);
    qDebug()<<sss;
    for(int i = 0; i< sss.size();++i)
    {
        QString aaa = sss.at(i);
        char *cp = aaa.toLatin1().data();
        ui ->comboBox ->addItem(tr(cp)) ;
    }

}

void MainWindow::on_ouv_clicked()
{
    //Ouvrir le dossier sélectionné
    QString path = ui->lineEdit ->text();
    path += "/";
    QString str = ui->comboBox->currentText();
    path += str;
    QString final;
    final = QFileDialog::getOpenFileName(this,tr("action"),path);
    Charger_filche(final);
}
