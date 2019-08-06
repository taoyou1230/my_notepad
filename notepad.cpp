#include "notepad.h"
#include "ui_notepad.h"

NotePad::NotePad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotePad)
{
    ui->setupUi(this);
}

NotePad::~NotePad()
{
    delete ui;
}

/**
 * 初始化
 * @brief NotePad::init
 */
void NotePad::init(){
    connect(ui->actionNew,SIGNAL(clicked()),this,SLOT(slotNew()));
}
/**
 * @brief NotePad::loadFromFile
 * @param fileName
 */
void NotePad::loadFromFile(QString fileName){

}

/******菜单项******/
/*文件*/
//新建
void NotePad::slotNew(){

}

//打开
void NotePad::slotOpen(){

}

//保存
void NotePad::slotSave(){

}
//另存为
void NotePad::slotSaveAs(){

}
//页面设置
void NotePad::slotPageSet(){

}
//打印
void NotePad::slotPrint(){

}
//退出
void NotePad::slotExit(){

}

/*编辑*/
//撤销
void NotePad::slotRevoke(){

}
//剪切
void NotePad::slotShear(){

}
//复制
void slotCopy(){

}
//粘贴
void NotePad::slotPaste(){

}
//删除
void NotePad::slotDelete(){

}
//查找
void NotePad::slotFind(){

}
//查找下一个
void NotePad::slotFindNext(){

}
//替换
void NotePad::slotReplace(){

}
//转到
void NotePad::slotGoto(){

}
//全选
void NotePad::slotSelectAll(){

}
//时间/日期
void NotePad::slotTimeOrDate(){

}

/*格式*/
//自行换行
void NotePad::slotWrapText(){

}
//字体
void NotePad::slotTypeface(){

}

/*查看*/
//状态栏
void NotePad::slotStatusBar(){

}

/*帮助*/
//查看帮助
void NotePad::slotViewHelp(){

}
//关于记事本
void NotePad::slotAbout(){

}
