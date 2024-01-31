<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>mainwindow</class>
 <widget class="QMainWindow" name="mainwindow">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>700</width>
    <height>500</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>Indexeur de Fichiers</string>
  </property>
  <widget class="QWidget" name="centralwidget">
   <layout class="QVBoxLayout" name="verticalLayout">
    <item>
     <layout class="QHBoxLayout" name="horizontalLayout_search">
      <item>
       <widget class="QLineEdit" name="lineEdit_query"/>
      </item>
      <item>
       <widget class="QPushButton" name="pushButton_search">
        <property name="text">
         <string>Rechercher</string>
        </property>
       </widget>
      </item>
      <item>
       <widget class="QComboBox" name="comboBox_filter">
        <item>
         <property name="text">
          <string>Tous les fichiers</string>
         </property>
        </item>
        <item>
         <property name="text">
          <string>Musiques</string>
         </property>
        </item>
        <item>
         <property name="text">
          <string>Vidéos</string>
         </property>
        </item>
        <item>
         <property name="text">
          <string>Images</string>
         </property>
        </item>
        <item>
         <property name="text">
          <string>Textes</string>
         </property>
        </item>
       </widget>
      </item>
     </layout>
    </item>
    <item>
     <widget class="QTableWidget" name="tableWidget_results">
      <property name="editTriggers">
       <set>QAbstractItemView::NoEditTriggers</set>
      </property>
      <property name="columnCount">
       <number>5</number>
      </property>
      <attribute name="horizontalHeaderCascadingSectionResizes">
       <bool>false</bool>
      </attribute>
      <attribute name="horizontalHeaderMinimumSectionSize">
       <number>35</number>
      </attribute>
      <attribute name="horizontalHeaderShowSortIndicator" stdset="0">
       <bool>false</bool>
      </attribute>
      <attribute name="verticalHeaderCascadingSectionResizes">
       <bool>false</bool>
      </attribute>
      <column>
       <property name="text">
        <string>Nom</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>Chemin</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>Modifié le</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>Type</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>Taille</string>
       </property>
      </column>
     </widget>
    </item>
    <item>
     <layout class="QHBoxLayout" name="horizontalLayout_directory">
      <item>
       <widget class="QLabel" name="label_directory">
        <property name="text">
         <string>Répertoire à indexer :</string>
        </property>
       </widget>
      </item>
      <item>
       <widget class="QLineEdit" name="lineEdit_directory"/>
      </item>
      <item>
       <widget class="QPushButton" name="pushButton_browse">
        <property name="text">
         <string>Parcourir</string>
        </property>
       </widget>
      </item>
     </layout>
    </item>
    <item>
     <layout class="QHBoxLayout" name="horizontalLayout_controls">
      <item>
       <widget class="QPushButton" name="pushButton_startIndexing">
        <property name="text">
         <string>Démarrer l'indexation</string>
        </property>
       </widget>
      </item>
      <item>
       <widget class="QPushButton" name="pushButton_pause">
        <property name="text">
         <string>Mettre en pause</string>
        </property>
       </widget>
      </item>
      <item>
       <widget class="QPushButton" name="pushButton_stopIndexing">
        <property name="text">
         <string>Arrêter l'indexation</string>
        </property>
       </widget>
      </item>
      <item>
       <widget class="QProgressBar" name="progressBar_indexing"/>
      </item>
     </layout>
    </item>
   </layout>
  </widget>
  <widget class="QMenuBar" name="menuBar">
   <property name="geometry">
    <rect>
     <x>0</x>
     <y>0</y>
     <width>700</width>
     <height>17</height>
    </rect>
   </property>
  </widget>
  <action name="actionA_propos">
   <property name="text">
    <string>A propos</string>
   </property>
  </action>
  <action name="actionOptions">
   <property name="text">
    <string>Options</string>
   </property>
  </action>
 </widget>
 <resources/>
 <connections/>
</ui>
