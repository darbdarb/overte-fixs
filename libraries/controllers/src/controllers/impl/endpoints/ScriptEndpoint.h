//
//  Created by Bradley Austin Davis 2015/10/23
//  Copyright 2015 High Fidelity, Inc.
//  Copyright 2023 Overte e.V.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//  SPDX-License-Identifier: Apache-2.0
//

#pragma once
#ifndef hifi_Controllers_ScriptEndpoint_h
#define hifi_Controllers_ScriptEndpoint_h

#include <ScriptValue.h>

#include "../Endpoint.h"

namespace controller {

class ScriptEndpoint : public Endpoint {
    Q_OBJECT;
public:
    using Endpoint::apply;
    ScriptEndpoint(const ScriptValue& callable)
        : Endpoint(Input::INVALID_INPUT), _callable(callable) {
    }

    virtual AxisValue peek() const override;
    virtual void apply(AxisValue newValue, const Pointer& source) override;

    virtual Pose peekPose() const override;
    virtual void apply(const Pose& newValue, const Pointer& source) override;

    virtual bool isPose() const override { return _returnPose; }
    virtual const ScriptEngine* getEngine() const { return _callable.engine().get(); }

protected:
    Q_INVOKABLE void updateValue();
    Q_INVOKABLE virtual void internalApply(float newValue, int sourceID);

    Q_INVOKABLE void updatePose();
    Q_INVOKABLE virtual void internalApply(const Pose& newValue, int sourceID);
private:
    ScriptValue _callable;
    float _lastValueRead { 0.0f };
    AxisValue _lastValueWritten { 0.0f, 0, false };

    bool _returnPose { false };
    Pose _lastPoseRead;
    Pose _lastPoseWritten;
};

}

#endif
