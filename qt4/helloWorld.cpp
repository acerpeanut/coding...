#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtCore/QTextCodec>
int main(int argc,char*argv[]){
	QApplication app(argc,argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QWidget* pWidget = new QWidget;
	QLabel label(pWidget);
	label.setText(QObject::tr("hello World !"));
	pWidget->show();
	return app.exec();
}
