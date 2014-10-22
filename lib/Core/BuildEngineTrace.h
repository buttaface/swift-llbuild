//===- BuildEngineTrace.h ---------------------------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef LLBUILD_CORE_BUILDENGINETRACE_H
#define LLBUILD_CORE_BUILDENGINETRACE_H

#include <string>

namespace llbuild {
namespace core {

class Rule;
class Task;

/// This class assists in writing build engine tracing information to an
/// external log file, suitable for ex post facto debugging and analysis.
class BuildEngineTrace {
    /// The output file pointer.
    void* OutputPtr;

    /// Whether the trace has been opened.
    bool IsOpen;

public:
    BuildEngineTrace();
    ~BuildEngineTrace();

    /// Open an output file for writing, must be called prior to any trace
    /// recording, and may only be called once per trace object.
    ///
    /// \returns True on success.
    bool open(const std::string& Path, std::string* Error_Out);

    /// Close the output file; no subsequest trace recording may be done.
    ///
    /// \returns True on success.
    bool close(std::string* Error_Out);

    /// Check if the trace output is open.
    bool isOpen() const { return IsOpen; }

    /// @name Trace Recording APIs
    /// @{

    void createdTaskForRule(const Task* Task, const Rule* Rule);
    void handlingTaskInputRequest(const Task* Task, const Rule* Rule);
    void readyingTaskInputRequest(const Task* Task, const Rule* Rule);
    void addedRulePendingTask(const Rule* Rule, const Task* Task);
    void completedTaskInputRequest(const Task* Task, const Rule* Rule);
    void updatedTaskWaitCount(const Task* Task, unsigned WaitCount);
    void unblockedTask(const Task* Task);
    void finishedTask(const Task* Task, const Rule* Rule);

    /// @}
};

}
}

#endif