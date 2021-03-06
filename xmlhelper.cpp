#include "xmlhelper.h"

XMLHelper::XMLHelper()
{
}

QDomElement XMLHelper::to_xml(QDomDocument *doc, QString name, float *array, int count)
{
    QDomElement e=doc->createElement(name+"s");

    for(int i=0;i<count;i++)
    {
        QDomElement node=doc->createElement(name);
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",(float)*(array+i));
        e.appendChild(node);
    }

    return e;
}

QDomElement XMLHelper::to_xml(QDomDocument *doc, QString name, int *array, int count)
{
    QDomElement e=doc->createElement(name+"s");

    for(int i=0;i<count;i++)
    {
        QDomElement node=doc->createElement(name);
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",(int)*(array+i));
        e.appendChild(node);
    }

    return e;
}

QDomElement XMLHelper::to_xml(QDomDocument *doc, QString name, double *array, int count)
{
    QDomElement e=doc->createElement(name+"s");

    for(int i=0;i<count;i++)
    {
        QDomElement node=doc->createElement(name);
        node.setAttribute("index",QString::number(i));
        node.setAttribute("value",(double)*(array+i));
        e.appendChild(node);
    }

    return e;
}

void XMLHelper::from_xml(QDomNode* node, QString name, float *array, int count)
{
    if(name+"s"!=node->toElement().tagName())
        return;
    QDomNode child[count];

    child[0]=node->firstChild();

    for(int i=1;i<count;i++)
    {
        child[i]=child[i-1].nextSibling();
    }

    for(int i=0;i<count;i++)
    {
        QDomElement e=child[i].toElement();
        QString v=e.attribute("value");
        *(array+i)=v.toFloat();
    }
}

void XMLHelper::from_xml(QDomNode *node,QString name, int *array, int count)
{
    if(name+"s"!=node->toElement().tagName())
        return;
    QDomNode child[count];

    child[0]=node->firstChild();

    for(int i=1;i<count;i++)
    {
        child[i]=child[i-1].nextSibling();
    }

    for(int i=0;i<count;i++)
    {
        QDomElement e=child[i].toElement();
        QString v=e.attribute("value");
        *(array+i)=v.toInt();
    }
}

void XMLHelper::from_xml(QDomNode *node, QString name, double *array, int count)
{
    if(name+"s"!=node->toElement().tagName())
        return;
    QDomNode child[count];

    child[0]=node->firstChild();

    for(int i=1;i<count;i++)
    {
        child[i]=child[i-1].nextSibling();
    }

    for(int i=0;i<count;i++)
    {
        QDomElement e=child[i].toElement();
        QString v=e.attribute("value");
        *(array+i)=v.toDouble();
    }
}

void XMLHelper::getAttribute(QDomElement *dom, QString name, double *a)
{
    if(dom->hasAttribute(name))
    {
        *a=dom->attribute(name).toDouble();
    }
}

void XMLHelper::getAttribute(QDomElement *dom, QString name, int *a)
{
    if(dom->hasAttribute(name))
    {
        *a=dom->attribute(name).toInt();
    }
}

void XMLHelper::getAttribute(QDomElement *dom, QString name, float *a)
{
    if(dom->hasAttribute(name))
    {
        *a=dom->attribute(name).toFloat();
    }
}

QString XMLHelper::getAttribute(QDomElement *dom, QString name)
{
    if(dom->hasAttribute(name))
    {
        return dom->attribute(name);
    }
    else
    {
        return "";
    }
}

/*
void XMLHelper::getAttribute(QDomElement *dom, QString name, QString* a)
{
    if(dom->hasAttribute(name))
    {
        std::string t=dom->attribute(name).toStdString();
        *a=QString::fromStdString(t);
    }
}
*/
