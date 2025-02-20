//
//  VariantMapToScriptValue.cpp
//  libraries/shared/src/
//
//  Created by Brad Hefta-Gaub on 12/6/13.
//  Copyright 2013 High Fidelity, Inc.
//  Copyright 2023 Overte e.V.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//  SPDX-License-Identifier: Apache-2.0
//

#include "VariantMapToScriptValue.h"

#include <QDebug>

#include "SharedLogging.h"

ScriptValue variantToScriptValue(QVariant& qValue, ScriptEngine& scriptEngine) {
    switch(qValue.type()) {
        case QVariant::Bool:
            return scriptEngine.newValue(qValue.toBool());
            break;
        case QVariant::Int:
            return scriptEngine.newValue(qValue.toInt());
            break;
        case QVariant::Double:
            return scriptEngine.newValue(qValue.toDouble());
            break;
        case QVariant::String:
        case QVariant::Url:
            return scriptEngine.newValue(qValue.toString());
            break;
        case QVariant::Map: {
            QVariantMap childMap = qValue.toMap();
            return variantMapToScriptValue(childMap, scriptEngine);
            break;
        }
        case QVariant::List: {
            QVariantList childList = qValue.toList();
            return variantListToScriptValue(childList, scriptEngine);
            break;
        }
        default:
            if (qValue.canConvert<float>()) {
                return scriptEngine.newValue(qValue.toFloat());
            }
            //qCDebug(shared) << "unhandled QScript type" << qValue.type();
            break;
    }

    return ScriptValue();
}


ScriptValue variantMapToScriptValue(QVariantMap& variantMap, ScriptEngine& scriptEngine) {
    ScriptValue scriptValue = scriptEngine.newObject();

    for (QVariantMap::const_iterator iter = variantMap.begin(); iter != variantMap.end(); ++iter) {
        QString key = iter.key();
        QVariant qValue = iter.value();
        scriptValue.setProperty(key, variantToScriptValue(qValue, scriptEngine));
    }

    return scriptValue;
}


ScriptValue variantListToScriptValue(QVariantList& variantList, ScriptEngine& scriptEngine) {

    ScriptValue scriptValue = scriptEngine.newArray();

    for (int i = 0; i < variantList.size(); i++) {
        scriptValue.setProperty(i, variantToScriptValue(variantList[i], scriptEngine));
    }

    return scriptValue;
}
