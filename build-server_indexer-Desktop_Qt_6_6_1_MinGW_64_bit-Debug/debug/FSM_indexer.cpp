//
// Statemachine code from reading SCXML file 'FSM_indexer.scxml'
// Created by: The Qt SCXML Compiler version 2 (Qt 6.6.1)
// WARNING! All changes made in this file will be lost!
//

#include "FSM_indexer.h"

#include <qscxmlinvokableservice.h>
#include <qscxmltabledata.h>
#include <QScxmlNullDataModel>

#if !defined(Q_QSCXMLC_OUTPUT_REVISION)
#error "The header file 'FSM_indexer.scxml' doesn't include <qscxmltabledata.h>."
#elif Q_QSCXMLC_OUTPUT_REVISION != 2
#error "This file was generated using the qscxmlc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The qscxmlc has changed too much.)"
#endif

struct FSM_indexer::Data: private QScxmlTableData {
    Data(FSM_indexer &stateMachine)
        : stateMachine(stateMachine)
    {}

    void init() {
        stateMachine.setTableData(this);
        stateMachine.setDataModel(&dataModel);
    }

    QString name() const override final
    { return string(0); }

    QScxmlExecutableContent::ContainerId initialSetup() const override final
    { return -1; }

    QScxmlExecutableContent::InstructionId *instructions() const override final
    { return theInstructions; }

    QScxmlExecutableContent::StringId *dataNames(int *count) const override final
    { *count = 0; return dataIds; }

    QScxmlExecutableContent::EvaluatorInfo evaluatorInfo(QScxmlExecutableContent::EvaluatorId evaluatorId) const override final
    { Q_ASSERT(evaluatorId >= 0); Q_ASSERT(evaluatorId < 0); return evaluators[evaluatorId]; }

    QScxmlExecutableContent::AssignmentInfo assignmentInfo(QScxmlExecutableContent::EvaluatorId assignmentId) const override final
    { Q_ASSERT(assignmentId >= 0); Q_ASSERT(assignmentId < 0); return assignments[assignmentId]; }

    QScxmlExecutableContent::ForeachInfo foreachInfo(QScxmlExecutableContent::EvaluatorId foreachId) const override final
    { Q_ASSERT(foreachId >= 0); Q_ASSERT(foreachId < 0); return foreaches[foreachId]; }

    QString string(QScxmlExecutableContent::StringId id) const override final
    {
        Q_ASSERT(id >= QScxmlExecutableContent::NoString); Q_ASSERT(id < 44);
        if (id == QScxmlExecutableContent::NoString) return QString();
        const auto dataOffset = strings.offsetsAndSize[id * 2];
        const auto dataSize = strings.offsetsAndSize[id * 2 + 1];
        return QString::fromRawData(reinterpret_cast<const QChar*>(&strings.stringdata[dataOffset]), dataSize);
    }

    const qint32 *stateMachineTable() const override final
    { return theStateMachineTable; }

    QScxmlInvokableServiceFactory *serviceFactory(int id) const override final;

    FSM_indexer &stateMachine;
    QScxmlNullDataModel dataModel;

    static QScxmlExecutableContent::ParameterInfo param(QScxmlExecutableContent::StringId name,
                                                        QScxmlExecutableContent::EvaluatorId expr,
                                                        QScxmlExecutableContent::StringId location)
    {
        QScxmlExecutableContent::ParameterInfo p;
        p.name = name;
        p.expr = expr;
        p.location = location;
        return p;
    }

    static QScxmlExecutableContent::InvokeInfo invoke(
            QScxmlExecutableContent::StringId id,
            QScxmlExecutableContent::StringId prefix,
            QScxmlExecutableContent::EvaluatorId expr,
            QScxmlExecutableContent::StringId location,
            QScxmlExecutableContent::StringId context,
            QScxmlExecutableContent::ContainerId finalize,
            bool autoforward)
    {
        QScxmlExecutableContent::InvokeInfo i;
        i.id = id;
        i.prefix = prefix;
        i.expr = expr;
        i.location = location;
        i.context = context;
        i.finalize = finalize;
        i.autoforward = autoforward;
        return i;
    }

    static qint32 theInstructions[];
    static QScxmlExecutableContent::StringId dataIds[];
    static QScxmlExecutableContent::EvaluatorInfo evaluators[];
    static QScxmlExecutableContent::AssignmentInfo assignments[];
    static QScxmlExecutableContent::ForeachInfo foreaches[];
    static const qint32 theStateMachineTable[];
    static struct Strings {
        const uint offsetsAndSize[44 * 2];
        char16_t stringdata[444];
    } strings;
};

FSM_indexer::FSM_indexer(QObject *parent)
    : QScxmlStateMachine(&staticMetaObject, parent)
    , data(new Data(*this))
{ qRegisterMetaType<FSM_indexer *>(); data->init(); }

FSM_indexer::~FSM_indexer()
{ delete data; }

QScxmlInvokableServiceFactory *FSM_indexer::Data::serviceFactory(int id) const
{
    Q_UNUSED(id);
    Q_UNREACHABLE();
}

qint32 FSM_indexer::Data::theInstructions[] = {
-1
};

QScxmlExecutableContent::StringId FSM_indexer::Data::dataIds[] = {
-1
};

QScxmlExecutableContent::EvaluatorInfo FSM_indexer::Data::evaluators[] = {
{ -1, -1 }
};

QScxmlExecutableContent::AssignmentInfo FSM_indexer::Data::assignments[] = {
{ -1, -1, -1 }
};

QScxmlExecutableContent::ForeachInfo FSM_indexer::Data::foreaches[] = {
{ -1, -1, -1, -1 }
};

FSM_indexer::Data::Strings FSM_indexer::Data::strings = {{
0, 11, 12, 6, 19, 9, 29, 9, 39, 11, 51, 16, 68, 10, 79, 11, 91, 7, 99, 6, 106, 7,
114, 13, 128, 12, 141, 7, 149, 8, 158, 12, 171, 8, 180, 4, 185, 3, 189, 4,
194, 9, 204, 7, 212, 13, 226, 10, 237, 6, 244, 10, 255, 9, 265, 7, 273, 12,
286, 9, 296, 11, 308, 15, 324, 14, 339, 6, 346, 12, 359, 12, 372, 5, 378, 7,
386, 9, 396, 4, 401, 13, 415, 13, 429, 3, 433, 9
},{
0x46,0x53,0x4d,0x5f,0x69,0x6e,0x64,0x65,0x78,0x65,0x72,0, // 0: FSM_indexer
0x53,0x45,0x41,0x52,0x43,0x48,0, // 1: SEARCH
0x69,0x73,0x5f,0x53,0x54,0x52,0x49,0x4e,0x47,0, // 2: is_STRING
0x53,0x61,0x76,0x65,0x56,0x61,0x6c,0x75,0x65,0, // 3: SaveValue
0x69,0x73,0x5f,0x4d,0x49,0x4e,0x5f,0x53,0x49,0x5a,0x45,0, // 4: is_MIN_SIZE
0x69,0x73,0x5f,0x4c,0x41,0x53,0x54,0x5f,0x4d,0x4f,0x44,0x49,0x46,0x49,0x45,0x44,0, // 5: is_LAST_MODIFIED
0x69,0x73,0x5f,0x43,0x52,0x45,0x41,0x54,0x45,0x44,0, // 6: is_CREATED
0x69,0x73,0x5f,0x4d,0x41,0x58,0x5f,0x53,0x49,0x5a,0x45,0, // 7: is_MAX_SIZE
0x69,0x73,0x5f,0x54,0x59,0x50,0x45,0, // 8: is_TYPE
0x69,0x73,0x5f,0x45,0x58,0x54,0, // 9: is_EXT
0x69,0x73,0x5f,0x53,0x49,0x5a,0x45,0, // 10: is_SIZE
0x4c,0x41,0x53,0x54,0x5f,0x4d,0x4f,0x44,0x49,0x46,0x49,0x45,0x44,0, // 11: LAST_MODIFIED
0x69,0x73,0x5f,0x64,0x61,0x74,0x65,0x5f,0x73,0x70,0x65,0x63,0, // 12: is_date_spec
0x43,0x52,0x45,0x41,0x54,0x45,0x44,0, // 13: CREATED
0x4d,0x41,0x58,0x5f,0x53,0x49,0x5a,0x45,0, // 14: MAX_SIZE
0x69,0x73,0x5f,0x73,0x69,0x7a,0x65,0x5f,0x73,0x70,0x65,0x63,0, // 15: is_size_spec
0x4d,0x49,0x4e,0x5f,0x53,0x49,0x5a,0x45,0, // 16: MIN_SIZE
0x53,0x49,0x5a,0x45,0, // 17: SIZE
0x45,0x58,0x54,0, // 18: EXT
0x54,0x59,0x50,0x45,0, // 19: TYPE
0x64,0x61,0x74,0x65,0x5f,0x73,0x70,0x65,0x63,0, // 20: date_spec
0x69,0x73,0x5f,0x44,0x41,0x54,0x45,0, // 21: is_DATE
0x69,0x73,0x5f,0x53,0x49,0x4e,0x43,0x45,0x5f,0x4c,0x41,0x53,0x54,0, // 22: is_SINCE_LAST
0x69,0x73,0x5f,0x42,0x45,0x54,0x57,0x45,0x45,0x4e,0, // 23: is_BETWEEN
0x69,0x73,0x5f,0x41,0x47,0x4f,0, // 24: is_AGO
0x53,0x49,0x4e,0x43,0x45,0x5f,0x4c,0x41,0x53,0x54,0, // 25: SINCE_LAST
0x69,0x73,0x5f,0x4e,0x55,0x4d,0x42,0x45,0x52,0, // 26: is_NUMBER
0x42,0x45,0x54,0x57,0x45,0x45,0x4e,0, // 27: BETWEEN
0x69,0x73,0x5f,0x53,0x49,0x5a,0x45,0x5f,0x53,0x50,0x45,0x43,0, // 28: is_SIZE_SPEC
0x73,0x69,0x7a,0x65,0x5f,0x73,0x70,0x65,0x63,0, // 29: size_spec
0x69,0x73,0x5f,0x4f,0x50,0x45,0x52,0x41,0x54,0x4f,0x52,0, // 30: is_OPERATOR
0x6c,0x69,0x73,0x74,0x5f,0x65,0x78,0x74,0x65,0x6e,0x73,0x69,0x6f,0x6e,0x73,0, // 31: list_extensions
0x74,0x79,0x70,0x65,0x5f,0x6c,0x69,0x73,0x74,0x5f,0x73,0x70,0x65,0x63,0, // 32: type_list_spec
0x4e,0x55,0x4d,0x42,0x45,0x52,0, // 33: NUMBER
0x69,0x73,0x5f,0x44,0x41,0x54,0x45,0x5f,0x55,0x4e,0x49,0x54,0, // 34: is_DATE_UNIT
0x69,0x73,0x5f,0x53,0x49,0x5a,0x45,0x5f,0x55,0x4e,0x49,0x54,0, // 35: is_SIZE_UNIT
0x56,0x45,0x52,0x49,0x46,0, // 36: VERIF
0x69,0x73,0x5f,0x4e,0x45,0x58,0x54,0, // 37: is_NEXT
0x44,0x41,0x54,0x45,0x5f,0x55,0x4e,0x49,0x54,0, // 38: DATE_UNIT
0x44,0x41,0x54,0x45,0, // 39: DATE
0x53,0x49,0x5a,0x45,0x5f,0x4f,0x50,0x45,0x52,0x41,0x54,0x4f,0x52,0, // 40: SIZE_OPERATOR
0x44,0x41,0x54,0x45,0x5f,0x4f,0x50,0x45,0x52,0x41,0x54,0x4f,0x52,0, // 41: DATE_OPERATOR
0x41,0x47,0x4f,0, // 42: AGO
0x53,0x49,0x5a,0x45,0x5f,0x55,0x4e,0x49,0x54,0 // 43: SIZE_UNIT
}};

const qint32 FSM_indexer::Data::theStateMachineTable[] = {
	0x2, // version
	0, // name
	0, // data-model
	199, // child states array offset
	38, // transition to initial states
	-1, // initial setup
	0, // binding
	-1, // maxServiceId
	14, 23, // state offset and count
	267, 39, // transition offset and count
	501, 225, // array offset and size

	// States:
	1, -1, 0, -1, -1, -1, -1, -1, -1, 4, -1,
	3, -1, 0, -1, -1, -1, -1, -1, -1, 34, -1,
	11, -1, 0, -1, -1, -1, -1, -1, -1, 46, -1,
	13, -1, 0, -1, -1, -1, -1, -1, -1, 52, -1,
	14, -1, 0, -1, -1, -1, -1, -1, -1, 58, -1,
	16, -1, 0, -1, -1, -1, -1, -1, -1, 64, -1,
	17, -1, 0, -1, -1, -1, -1, -1, -1, 70, -1,
	18, -1, 0, -1, -1, -1, -1, -1, -1, 74, -1,
	19, -1, 0, -1, -1, -1, -1, -1, -1, 78, -1,
	20, -1, 0, -1, -1, -1, -1, -1, -1, 96, -1,
	25, -1, 0, -1, -1, -1, -1, -1, -1, 105, -1,
	27, -1, 0, -1, -1, -1, -1, -1, -1, 115, -1,
	29, -1, 0, -1, -1, -1, -1, -1, -1, 126, -1,
	31, -1, 0, -1, -1, -1, -1, -1, -1, 135, -1,
	32, -1, 0, -1, -1, -1, -1, -1, -1, 144, -1,
	33, -1, 0, -1, -1, -1, -1, -1, -1, 155, -1,
	36, -1, 0, -1, -1, -1, -1, -1, -1, 162, -1,
	38, -1, 0, -1, -1, -1, -1, -1, -1, 166, -1,
	39, -1, 0, -1, -1, -1, -1, -1, -1, 174, -1,
	40, -1, 0, -1, -1, -1, -1, -1, -1, 181, -1,
	41, -1, 0, -1, -1, -1, -1, -1, -1, 187, -1,
	42, -1, 0, -1, -1, -1, -1, -1, -1, 193, -1,
	43, -1, 0, -1, -1, -1, -1, -1, -1, 197, -1,

	// Transitions:
	2, -1, 1, 0, 0, -1, 
	8, -1, 1, 1, 6, -1, 
	12, -1, 1, 1, 10, -1, 
	16, -1, 1, 1, 14, -1, 
	20, -1, 1, 1, 18, -1, 
	24, -1, 1, 1, 22, -1, 
	28, -1, 1, 1, 26, -1, 
	32, -1, 1, 1, 30, -1, 
	44, -1, 1, 2, 42, -1, 
	50, -1, 1, 3, 48, -1, 
	56, -1, 1, 4, 54, -1, 
	62, -1, 1, 5, 60, -1, 
	68, -1, 1, 6, 66, -1, 
	-1, -1, 1, 7, 72, -1, 
	-1, -1, 1, 8, 76, -1, 
	82, -1, 1, 9, 80, -1, 
	86, -1, 1, 9, 84, -1, 
	90, -1, 1, 9, 88, -1, 
	94, -1, 1, 9, 92, -1, 
	103, -1, 1, 10, 101, -1, 
	109, -1, 1, 11, 107, -1, 
	113, -1, 1, 11, 111, -1, 
	120, -1, 1, 12, 118, -1, 
	124, -1, 1, 12, 122, -1, 
	-1, -1, 1, 13, 129, -1, 
	133, -1, 1, 13, 131, -1, 
	-1, -1, 1, 14, 138, -1, 
	142, -1, 1, 14, 140, -1, 
	149, -1, 1, 15, 147, -1, 
	153, -1, 1, 15, 151, -1, 
	160, -1, 1, 16, 158, -1, 
	-1, -1, 1, 17, 164, -1, 
	-1, -1, 1, 18, 168, -1, 
	172, -1, 1, 18, 170, -1, 
	179, -1, 1, 19, 177, -1, 
	185, -1, 1, 20, 183, -1, 
	191, -1, 1, 21, 189, -1, 
	-1, -1, 1, 22, 195, -1, 
	-1, -1, 2, -1, 223, -1, 

	// Arrays:
	1, 1, 
	1, 2, 
	1, 0, 
	1, 5, 
	1, 4, 
	1, 2, 
	1, 5, 
	1, 3, 
	1, 6, 
	1, 4, 
	1, 7, 
	1, 8, 
	1, 8, 
	1, 7, 
	1, 9, 
	1, 6, 
	1, 10, 
	7, 1, 2, 3, 4, 5, 6, 7, 
	1, 9, 
	1, 12, 
	1, 8, 
	1, 9, 
	1, 12, 
	1, 9, 
	1, 12, 
	1, 15, 
	1, 10, 
	1, 12, 
	1, 15, 
	1, 11, 
	1, 12, 
	1, 15, 
	1, 12, 
	1, 13, 
	1, 13, 
	1, 14, 
	1, 14, 
	1, 18, 
	1, 21, 
	1, 10, 
	1, 22, 
	1, 11, 
	1, 23, 
	1, 21, 
	1, 24, 
	4, 15, 16, 17, 18, 
	1, 15, 
	1, 26, 
	1, 19, 
	1, 18, 
	1, 21, 
	1, 12, 
	1, 28, 
	2, 20, 21, 
	1, 19, 
	1, 30, 
	1, 15, 
	1, 26, 
	2, 22, 23, 
	1, 16, 
	1, 13, 
	1, 9, 
	2, 24, 25, 
	1, 16, 
	1, 14, 
	1, 8, 
	2, 26, 27, 
	1, 17, 
	1, 34, 
	1, 22, 
	1, 35, 
	2, 28, 29, 
	1, 1, 
	1, 37, 
	1, 30, 
	1, 16, 
	1, 31, 
	1, 16, 
	1, 20, 
	1, 30, 
	2, 32, 33, 
	1, 12, 
	1, 28, 
	1, 34, 
	1, 18, 
	1, 21, 
	1, 35, 
	1, 15, 
	1, 26, 
	1, 36, 
	1, 16, 
	1, 37, 
	23, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
	1, 0, 

	0xc0ff33 // terminator
};

namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFSM_indexerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFSM_indexerENDCLASS = QtMocHelpers::stringData(
    "FSM_indexer",
    "SEARCHChanged",
    "",
    "active",
    "SaveValueChanged",
    "LAST_MODIFIEDChanged",
    "CREATEDChanged",
    "MAX_SIZEChanged",
    "MIN_SIZEChanged",
    "SIZEChanged",
    "EXTChanged",
    "TYPEChanged",
    "date_specChanged",
    "SINCE_LASTChanged",
    "BETWEENChanged",
    "size_specChanged",
    "list_extensionsChanged",
    "type_list_specChanged",
    "NUMBERChanged",
    "VERIFChanged",
    "DATE_UNITChanged",
    "DATEChanged",
    "SIZE_OPERATORChanged",
    "DATE_OPERATORChanged",
    "AGOChanged",
    "SIZE_UNITChanged",
    "QObject *",
    "parent",
    "SEARCH",
    "SaveValue",
    "LAST_MODIFIED",
    "CREATED",
    "MAX_SIZE",
    "MIN_SIZE",
    "SIZE",
    "EXT",
    "TYPE",
    "date_spec",
    "SINCE_LAST",
    "BETWEEN",
    "size_spec",
    "list_extensions",
    "type_list_spec",
    "NUMBER",
    "VERIF",
    "DATE_UNIT",
    "DATE",
    "SIZE_OPERATOR",
    "DATE_OPERATOR",
    "AGO",
    "SIZE_UNIT"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFSM_indexerENDCLASS_t {
    uint offsetsAndSizes[102];
    char stringdata0[12];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[17];
    char stringdata5[21];
    char stringdata6[15];
    char stringdata7[16];
    char stringdata8[16];
    char stringdata9[12];
    char stringdata10[11];
    char stringdata11[12];
    char stringdata12[17];
    char stringdata13[18];
    char stringdata14[15];
    char stringdata15[17];
    char stringdata16[23];
    char stringdata17[22];
    char stringdata18[14];
    char stringdata19[13];
    char stringdata20[17];
    char stringdata21[12];
    char stringdata22[21];
    char stringdata23[21];
    char stringdata24[11];
    char stringdata25[17];
    char stringdata26[10];
    char stringdata27[7];
    char stringdata28[7];
    char stringdata29[10];
    char stringdata30[14];
    char stringdata31[8];
    char stringdata32[9];
    char stringdata33[9];
    char stringdata34[5];
    char stringdata35[4];
    char stringdata36[5];
    char stringdata37[10];
    char stringdata38[11];
    char stringdata39[8];
    char stringdata40[10];
    char stringdata41[16];
    char stringdata42[15];
    char stringdata43[7];
    char stringdata44[6];
    char stringdata45[10];
    char stringdata46[5];
    char stringdata47[14];
    char stringdata48[14];
    char stringdata49[4];
    char stringdata50[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFSM_indexerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFSM_indexerENDCLASS_t qt_meta_stringdata_CLASSFSM_indexerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "FSM_indexer"
        QT_MOC_LITERAL(12, 13),  // "SEARCHChanged"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 6),  // "active"
        QT_MOC_LITERAL(34, 16),  // "SaveValueChanged"
        QT_MOC_LITERAL(51, 20),  // "LAST_MODIFIEDChanged"
        QT_MOC_LITERAL(72, 14),  // "CREATEDChanged"
        QT_MOC_LITERAL(87, 15),  // "MAX_SIZEChanged"
        QT_MOC_LITERAL(103, 15),  // "MIN_SIZEChanged"
        QT_MOC_LITERAL(119, 11),  // "SIZEChanged"
        QT_MOC_LITERAL(131, 10),  // "EXTChanged"
        QT_MOC_LITERAL(142, 11),  // "TYPEChanged"
        QT_MOC_LITERAL(154, 16),  // "date_specChanged"
        QT_MOC_LITERAL(171, 17),  // "SINCE_LASTChanged"
        QT_MOC_LITERAL(189, 14),  // "BETWEENChanged"
        QT_MOC_LITERAL(204, 16),  // "size_specChanged"
        QT_MOC_LITERAL(221, 22),  // "list_extensionsChanged"
        QT_MOC_LITERAL(244, 21),  // "type_list_specChanged"
        QT_MOC_LITERAL(266, 13),  // "NUMBERChanged"
        QT_MOC_LITERAL(280, 12),  // "VERIFChanged"
        QT_MOC_LITERAL(293, 16),  // "DATE_UNITChanged"
        QT_MOC_LITERAL(310, 11),  // "DATEChanged"
        QT_MOC_LITERAL(322, 20),  // "SIZE_OPERATORChanged"
        QT_MOC_LITERAL(343, 20),  // "DATE_OPERATORChanged"
        QT_MOC_LITERAL(364, 10),  // "AGOChanged"
        QT_MOC_LITERAL(375, 16),  // "SIZE_UNITChanged"
        QT_MOC_LITERAL(392, 9),  // "QObject *"
        QT_MOC_LITERAL(402, 6),  // "parent"
        QT_MOC_LITERAL(409, 6),  // "SEARCH"
        QT_MOC_LITERAL(416, 9),  // "SaveValue"
        QT_MOC_LITERAL(426, 13),  // "LAST_MODIFIED"
        QT_MOC_LITERAL(440, 7),  // "CREATED"
        QT_MOC_LITERAL(448, 8),  // "MAX_SIZE"
        QT_MOC_LITERAL(457, 8),  // "MIN_SIZE"
        QT_MOC_LITERAL(466, 4),  // "SIZE"
        QT_MOC_LITERAL(471, 3),  // "EXT"
        QT_MOC_LITERAL(475, 4),  // "TYPE"
        QT_MOC_LITERAL(480, 9),  // "date_spec"
        QT_MOC_LITERAL(490, 10),  // "SINCE_LAST"
        QT_MOC_LITERAL(501, 7),  // "BETWEEN"
        QT_MOC_LITERAL(509, 9),  // "size_spec"
        QT_MOC_LITERAL(519, 15),  // "list_extensions"
        QT_MOC_LITERAL(535, 14),  // "type_list_spec"
        QT_MOC_LITERAL(550, 6),  // "NUMBER"
        QT_MOC_LITERAL(557, 5),  // "VERIF"
        QT_MOC_LITERAL(563, 9),  // "DATE_UNIT"
        QT_MOC_LITERAL(573, 4),  // "DATE"
        QT_MOC_LITERAL(578, 13),  // "SIZE_OPERATOR"
        QT_MOC_LITERAL(592, 13),  // "DATE_OPERATOR"
        QT_MOC_LITERAL(606, 3),  // "AGO"
        QT_MOC_LITERAL(610, 9)   // "SIZE_UNIT"
    },
    {char(0x46),char(0x53),char(0x4d),char(0x5f),char(0x69),char(0x6e),char(0x64),char(0x65),char(0x78),char(0x65),char(0x72),0}, // 0: FSM_indexer
    {char(0x53),char(0x45),char(0x41),char(0x52),char(0x43),char(0x48),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 1: SEARCHChanged
    {0}, // 2: 
    {char(0x61),char(0x63),char(0x74),char(0x69),char(0x76),char(0x65),0}, // 3: active
    {char(0x53),char(0x61),char(0x76),char(0x65),char(0x56),char(0x61),char(0x6c),char(0x75),char(0x65),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 4: SaveValueChanged
    {char(0x4c),char(0x41),char(0x53),char(0x54),char(0x5f),char(0x4d),char(0x4f),char(0x44),char(0x49),char(0x46),char(0x49),char(0x45),char(0x44),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 5: LAST_MODIFIEDChanged
    {char(0x43),char(0x52),char(0x45),char(0x41),char(0x54),char(0x45),char(0x44),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 6: CREATEDChanged
    {char(0x4d),char(0x41),char(0x58),char(0x5f),char(0x53),char(0x49),char(0x5a),char(0x45),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 7: MAX_SIZEChanged
    {char(0x4d),char(0x49),char(0x4e),char(0x5f),char(0x53),char(0x49),char(0x5a),char(0x45),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 8: MIN_SIZEChanged
    {char(0x53),char(0x49),char(0x5a),char(0x45),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 9: SIZEChanged
    {char(0x45),char(0x58),char(0x54),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 10: EXTChanged
    {char(0x54),char(0x59),char(0x50),char(0x45),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 11: TYPEChanged
    {char(0x64),char(0x61),char(0x74),char(0x65),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 12: date_specChanged
    {char(0x53),char(0x49),char(0x4e),char(0x43),char(0x45),char(0x5f),char(0x4c),char(0x41),char(0x53),char(0x54),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 13: SINCE_LASTChanged
    {char(0x42),char(0x45),char(0x54),char(0x57),char(0x45),char(0x45),char(0x4e),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 14: BETWEENChanged
    {char(0x73),char(0x69),char(0x7a),char(0x65),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 15: size_specChanged
    {char(0x6c),char(0x69),char(0x73),char(0x74),char(0x5f),char(0x65),char(0x78),char(0x74),char(0x65),char(0x6e),char(0x73),char(0x69),char(0x6f),char(0x6e),char(0x73),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 16: list_extensionsChanged
    {char(0x74),char(0x79),char(0x70),char(0x65),char(0x5f),char(0x6c),char(0x69),char(0x73),char(0x74),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 17: type_list_specChanged
    {char(0x4e),char(0x55),char(0x4d),char(0x42),char(0x45),char(0x52),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 18: NUMBERChanged
    {char(0x56),char(0x45),char(0x52),char(0x49),char(0x46),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 19: VERIFChanged
    {char(0x44),char(0x41),char(0x54),char(0x45),char(0x5f),char(0x55),char(0x4e),char(0x49),char(0x54),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 20: DATE_UNITChanged
    {char(0x44),char(0x41),char(0x54),char(0x45),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 21: DATEChanged
    {char(0x53),char(0x49),char(0x5a),char(0x45),char(0x5f),char(0x4f),char(0x50),char(0x45),char(0x52),char(0x41),char(0x54),char(0x4f),char(0x52),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 22: SIZE_OPERATORChanged
    {char(0x44),char(0x41),char(0x54),char(0x45),char(0x5f),char(0x4f),char(0x50),char(0x45),char(0x52),char(0x41),char(0x54),char(0x4f),char(0x52),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 23: DATE_OPERATORChanged
    {char(0x41),char(0x47),char(0x4f),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 24: AGOChanged
    {char(0x53),char(0x49),char(0x5a),char(0x45),char(0x5f),char(0x55),char(0x4e),char(0x49),char(0x54),char(0x43),char(0x68),char(0x61),char(0x6e),char(0x67),char(0x65),char(0x64),0}, // 25: SIZE_UNITChanged
    {char(0x51),char(0x4f),char(0x62),char(0x6a),char(0x65),char(0x63),char(0x74),char(0x20),char(0x2a),0}, // 26: QObject *
    {char(0x70),char(0x61),char(0x72),char(0x65),char(0x6e),char(0x74),0}, // 27: parent
    {char(0x53),char(0x45),char(0x41),char(0x52),char(0x43),char(0x48),0}, // 28: SEARCH
    {char(0x53),char(0x61),char(0x76),char(0x65),char(0x56),char(0x61),char(0x6c),char(0x75),char(0x65),0}, // 29: SaveValue
    {char(0x4c),char(0x41),char(0x53),char(0x54),char(0x5f),char(0x4d),char(0x4f),char(0x44),char(0x49),char(0x46),char(0x49),char(0x45),char(0x44),0}, // 30: LAST_MODIFIED
    {char(0x43),char(0x52),char(0x45),char(0x41),char(0x54),char(0x45),char(0x44),0}, // 31: CREATED
    {char(0x4d),char(0x41),char(0x58),char(0x5f),char(0x53),char(0x49),char(0x5a),char(0x45),0}, // 32: MAX_SIZE
    {char(0x4d),char(0x49),char(0x4e),char(0x5f),char(0x53),char(0x49),char(0x5a),char(0x45),0}, // 33: MIN_SIZE
    {char(0x53),char(0x49),char(0x5a),char(0x45),0}, // 34: SIZE
    {char(0x45),char(0x58),char(0x54),0}, // 35: EXT
    {char(0x54),char(0x59),char(0x50),char(0x45),0}, // 36: TYPE
    {char(0x64),char(0x61),char(0x74),char(0x65),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),0}, // 37: date_spec
    {char(0x53),char(0x49),char(0x4e),char(0x43),char(0x45),char(0x5f),char(0x4c),char(0x41),char(0x53),char(0x54),0}, // 38: SINCE_LAST
    {char(0x42),char(0x45),char(0x54),char(0x57),char(0x45),char(0x45),char(0x4e),0}, // 39: BETWEEN
    {char(0x73),char(0x69),char(0x7a),char(0x65),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),0}, // 40: size_spec
    {char(0x6c),char(0x69),char(0x73),char(0x74),char(0x5f),char(0x65),char(0x78),char(0x74),char(0x65),char(0x6e),char(0x73),char(0x69),char(0x6f),char(0x6e),char(0x73),0}, // 41: list_extensions
    {char(0x74),char(0x79),char(0x70),char(0x65),char(0x5f),char(0x6c),char(0x69),char(0x73),char(0x74),char(0x5f),char(0x73),char(0x70),char(0x65),char(0x63),0}, // 42: type_list_spec
    {char(0x4e),char(0x55),char(0x4d),char(0x42),char(0x45),char(0x52),0}, // 43: NUMBER
    {char(0x56),char(0x45),char(0x52),char(0x49),char(0x46),0}, // 44: VERIF
    {char(0x44),char(0x41),char(0x54),char(0x45),char(0x5f),char(0x55),char(0x4e),char(0x49),char(0x54),0}, // 45: DATE_UNIT
    {char(0x44),char(0x41),char(0x54),char(0x45),0}, // 46: DATE
    {char(0x53),char(0x49),char(0x5a),char(0x45),char(0x5f),char(0x4f),char(0x50),char(0x45),char(0x52),char(0x41),char(0x54),char(0x4f),char(0x52),0}, // 47: SIZE_OPERATOR
    {char(0x44),char(0x41),char(0x54),char(0x45),char(0x5f),char(0x4f),char(0x50),char(0x45),char(0x52),char(0x41),char(0x54),char(0x4f),char(0x52),0}, // 48: DATE_OPERATOR
    {char(0x41),char(0x47),char(0x4f),0}, // 49: AGO
    {char(0x53),char(0x49),char(0x5a),char(0x45),char(0x5f),char(0x55),char(0x4e),char(0x49),char(0x54),0} // 50: SIZE_UNIT
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFSM_indexerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
      23,  224, // properties
       0,    0, // enums/sets
       1,  339, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  152,    2, 0x06,   24 /* Public */,
       4,    1,  155,    2, 0x06,   26 /* Public */,
       5,    1,  158,    2, 0x06,   28 /* Public */,
       6,    1,  161,    2, 0x06,   30 /* Public */,
       7,    1,  164,    2, 0x06,   32 /* Public */,
       8,    1,  167,    2, 0x06,   34 /* Public */,
       9,    1,  170,    2, 0x06,   36 /* Public */,
      10,    1,  173,    2, 0x06,   38 /* Public */,
      11,    1,  176,    2, 0x06,   40 /* Public */,
      12,    1,  179,    2, 0x06,   42 /* Public */,
      13,    1,  182,    2, 0x06,   44 /* Public */,
      14,    1,  185,    2, 0x06,   46 /* Public */,
      15,    1,  188,    2, 0x06,   48 /* Public */,
      16,    1,  191,    2, 0x06,   50 /* Public */,
      17,    1,  194,    2, 0x06,   52 /* Public */,
      18,    1,  197,    2, 0x06,   54 /* Public */,
      19,    1,  200,    2, 0x06,   56 /* Public */,
      20,    1,  203,    2, 0x06,   58 /* Public */,
      21,    1,  206,    2, 0x06,   60 /* Public */,
      22,    1,  209,    2, 0x06,   62 /* Public */,
      23,    1,  212,    2, 0x06,   64 /* Public */,
      24,    1,  215,    2, 0x06,   66 /* Public */,
      25,    1,  218,    2, 0x06,   68 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

 // constructors: parameters
    0x80000000 | 2, 0x80000000 | 26,   27,

 // properties: name, type, flags
      28, QMetaType::Bool, 0x00115001, uint(0), 0,
      29, QMetaType::Bool, 0x00115001, uint(1), 0,
      30, QMetaType::Bool, 0x00115001, uint(2), 0,
      31, QMetaType::Bool, 0x00115001, uint(3), 0,
      32, QMetaType::Bool, 0x00115001, uint(4), 0,
      33, QMetaType::Bool, 0x00115001, uint(5), 0,
      34, QMetaType::Bool, 0x00115001, uint(6), 0,
      35, QMetaType::Bool, 0x00115001, uint(7), 0,
      36, QMetaType::Bool, 0x00115001, uint(8), 0,
      37, QMetaType::Bool, 0x00115001, uint(9), 0,
      38, QMetaType::Bool, 0x00115001, uint(10), 0,
      39, QMetaType::Bool, 0x00115001, uint(11), 0,
      40, QMetaType::Bool, 0x00115001, uint(12), 0,
      41, QMetaType::Bool, 0x00115001, uint(13), 0,
      42, QMetaType::Bool, 0x00115001, uint(14), 0,
      43, QMetaType::Bool, 0x00115001, uint(15), 0,
      44, QMetaType::Bool, 0x00115001, uint(16), 0,
      45, QMetaType::Bool, 0x00115001, uint(17), 0,
      46, QMetaType::Bool, 0x00115001, uint(18), 0,
      47, QMetaType::Bool, 0x00115001, uint(19), 0,
      48, QMetaType::Bool, 0x00115001, uint(20), 0,
      49, QMetaType::Bool, 0x00115001, uint(21), 0,
      50, QMetaType::Bool, 0x00115001, uint(22), 0,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    1,  221,    2, 0x0e,   70 /* Public */,

       0        // eod
};

Q_CONSTINIT const QMetaObject FSM_indexer::staticMetaObject = { {
    QMetaObject::SuperData::link<QScxmlStateMachine::staticMetaObject>(),
    qt_meta_stringdata_CLASSFSM_indexerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFSM_indexerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFSM_indexerENDCLASS_t,
        // property 'SEARCH'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'SaveValue'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'LAST_MODIFIED'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'CREATED'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'MAX_SIZE'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'MIN_SIZE'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'SIZE'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'EXT'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'TYPE'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'date_spec'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'SINCE_LAST'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'BETWEEN'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'size_spec'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'list_extensions'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'type_list_spec'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'NUMBER'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'VERIF'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'DATE_UNIT'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'DATE'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'SIZE_OPERATOR'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'DATE_OPERATOR'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'AGO'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'SIZE_UNIT'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FSM_indexer, std::true_type>,
        // method 'SEARCHChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'SaveValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'LAST_MODIFIEDChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'CREATEDChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'MAX_SIZEChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'MIN_SIZEChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'SIZEChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'EXTChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'TYPEChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'date_specChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'SINCE_LASTChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'BETWEENChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'size_specChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'list_extensionsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'type_list_specChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'NUMBERChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'VERIFChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'DATE_UNITChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'DATEChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'SIZE_OPERATORChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'DATE_OPERATORChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'AGOChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'SIZE_UNITChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // constructor 'FSM_indexer'
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>
    >,
    nullptr
} };

void FSM_indexer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { FSM_indexer *_r = new FSM_indexer((*reinterpret_cast<QObject **>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::ConstructInPlace) {
        switch (_id) {
        case 0: { new (_a[0]) FSM_indexer((*reinterpret_cast<QObject **>(_a[1]))); } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FSM_indexer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: QMetaObject::activate(_o, &staticMetaObject, 0, _a); break;
        case 1: QMetaObject::activate(_o, &staticMetaObject, 1, _a); break;
        case 2: QMetaObject::activate(_o, &staticMetaObject, 2, _a); break;
        case 3: QMetaObject::activate(_o, &staticMetaObject, 3, _a); break;
        case 4: QMetaObject::activate(_o, &staticMetaObject, 4, _a); break;
        case 5: QMetaObject::activate(_o, &staticMetaObject, 5, _a); break;
        case 6: QMetaObject::activate(_o, &staticMetaObject, 6, _a); break;
        case 7: QMetaObject::activate(_o, &staticMetaObject, 7, _a); break;
        case 8: QMetaObject::activate(_o, &staticMetaObject, 8, _a); break;
        case 9: QMetaObject::activate(_o, &staticMetaObject, 9, _a); break;
        case 10: QMetaObject::activate(_o, &staticMetaObject, 10, _a); break;
        case 11: QMetaObject::activate(_o, &staticMetaObject, 11, _a); break;
        case 12: QMetaObject::activate(_o, &staticMetaObject, 12, _a); break;
        case 13: QMetaObject::activate(_o, &staticMetaObject, 13, _a); break;
        case 14: QMetaObject::activate(_o, &staticMetaObject, 14, _a); break;
        case 15: QMetaObject::activate(_o, &staticMetaObject, 15, _a); break;
        case 16: QMetaObject::activate(_o, &staticMetaObject, 16, _a); break;
        case 17: QMetaObject::activate(_o, &staticMetaObject, 17, _a); break;
        case 18: QMetaObject::activate(_o, &staticMetaObject, 18, _a); break;
        case 19: QMetaObject::activate(_o, &staticMetaObject, 19, _a); break;
        case 20: QMetaObject::activate(_o, &staticMetaObject, 20, _a); break;
        case 21: QMetaObject::activate(_o, &staticMetaObject, 21, _a); break;
        case 22: QMetaObject::activate(_o, &staticMetaObject, 22, _a); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        (void)result;
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FSM_indexer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isActive(0); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isActive(1); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isActive(2); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isActive(3); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isActive(4); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isActive(5); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->isActive(6); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->isActive(7); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->isActive(8); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->isActive(9); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->isActive(10); break;
        case 11: *reinterpret_cast< bool*>(_v) = _t->isActive(11); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->isActive(12); break;
        case 13: *reinterpret_cast< bool*>(_v) = _t->isActive(13); break;
        case 14: *reinterpret_cast< bool*>(_v) = _t->isActive(14); break;
        case 15: *reinterpret_cast< bool*>(_v) = _t->isActive(15); break;
        case 16: *reinterpret_cast< bool*>(_v) = _t->isActive(16); break;
        case 17: *reinterpret_cast< bool*>(_v) = _t->isActive(17); break;
        case 18: *reinterpret_cast< bool*>(_v) = _t->isActive(18); break;
        case 19: *reinterpret_cast< bool*>(_v) = _t->isActive(19); break;
        case 20: *reinterpret_cast< bool*>(_v) = _t->isActive(20); break;
        case 21: *reinterpret_cast< bool*>(_v) = _t->isActive(21); break;
        case 22: *reinterpret_cast< bool*>(_v) = _t->isActive(22); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *FSM_indexer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FSM_indexer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFSM_indexerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QScxmlStateMachine::qt_metacast(_clname);
}

int FSM_indexer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScxmlStateMachine::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

