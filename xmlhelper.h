#ifndef XMLHELPER_H
#define XMLHELPER_H
#include <QDomDocument>

class XMLHelper
{
public:
    XMLHelper();
    static QDomElement to_xml(QDomDocument* doc,QString name,float* array,int count );
    static QDomElement to_xml(QDomDocument* doc,QString name,int* array,int count );
    static QDomElement to_xml(QDomDocument* doc,QString name,double* array,int count );

    static void from_xml(QDomNode *node, QString name, float* array, int count);
    static void from_xml(QDomNode *node,QString name, int* array, int count);
    static void from_xml(QDomNode *node,QString name, double* array, int count);

    static void getAttribute(QDomElement* dom,QString name,double* a);
    static void getAttribute(QDomElement* dom,QString name,int* a);
    static void getAttribute(QDomElement* dom,QString name,float* a);

};

#endif // XMLHELPER_H
