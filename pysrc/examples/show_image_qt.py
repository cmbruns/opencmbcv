#!/usr/bin/python

# icon_qt.py

import sys
from PyQt4 import QtGui, QtCore

class ShowImage(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.resize(250, 150)
        self.setWindowTitle('ShowImage')
        # Little icon for the upper left corner
        self.setWindowIcon(QtGui.QIcon('images/penguin.png'))
        # Hover the mouse to see tooltip documentation
        self.setToolTip('Please stop <b>staring</b> at the penguin! (He\'s shy)')
        # Load image
        img = QtGui.QImage('images/stereo_test_100px.jpg')
        pix = QtGui.QPixmap.fromImage(img)
        imageLabel = QtGui.QLabel()
        imageLabel.setPixmap(pix)
        self.setCentralWidget(imageLabel)
        # status bar
        self.statusBar().showMessage('Ready')
        # exit action
        exit = QtGui.QAction(QtGui.QIcon('images/Crystal_Clear_action_exit.png'), 'Exit', self)
        exit.setShortcut('Ctrl+Q')
        exit.setStatusTip('Exit application')
        self.connect(exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))
        # menu bar
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        file.addAction(exit)
            
    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Confirm Exit',
            "Are you sure to quit?", 
            QtGui.QMessageBox.Yes, 
            QtGui.QMessageBox.No)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


app = QtGui.QApplication(sys.argv)
showImage = ShowImage()
showImage.show()
sys.exit(app.exec_())
