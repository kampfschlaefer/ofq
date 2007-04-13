#ifndef QOSCTYPES_H
#define QOSCTYPES_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QVariant>

/**
 * @file Will contain the conversions from Qt-types to OSC-types
 */

/**
 */
QByteArray oscMessage( QString path, QVariant );

#endif // QOSCTYPES_H

