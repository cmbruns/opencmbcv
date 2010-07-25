#!/usr/bin/python

# icon_qt.py

import sys
from PyQt4 import QtGui, QtCore

class Icon(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Icon')
        # Little icon for the upper left corner
        self.setWindowIcon(QtGui.QIcon('images/penguin.png'))
        # Hover the mouse to see tooltip documentation
        self.setToolTip('Please stop <b>staring</b> at the penguin! (He\'s shy)')
        # Add a quit button, demonstrating signals and slots
        # TODO - why does pressing the button not invoke the "closeEvent()" method
        quit = QtGui.QPushButton('Close', self)
        quit.setGeometry(10, 10, 60, 35)
        self.connect(quit, QtCore.SIGNAL('clicked()'),
            QtGui.qApp, QtCore.SLOT('quit()'))
        # Place the app in the middle of the screen
        self.center()
            
    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message',
            "Are you sure to quit?", 
            QtGui.QMessageBox.Yes, 
            QtGui.QMessageBox.No)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
            
    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size =  self.geometry()
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)


app = QtGui.QApplication(sys.argv)
icon = Icon()
icon.show()

sys.exit(app.exec_())
