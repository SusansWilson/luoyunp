//
// Copyright (C) 2017~2017 by CSSlayer
// wengxt@gmail.com
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; see the file COPYING. If not,
// see <http://www.gnu.org/licenses/>.
//

#include "inputpanel.h"

namespace fcitx {

class InputPanelPrivate {
public:
    Text auxDown_;
    Text auxUp_;
    Text preedit_;
    Text clientPreedit_;
    std::shared_ptr<CandidateList> candidate_;
    InputContext *ic_;
};

InputPanel::InputPanel(InputContext *ic)
    : d_ptr(std::make_unique<InputPanelPrivate>()) {
    FCITX_D();
    d->ic_ = ic;
}

InputPanel::~InputPanel() {}

void InputPanel::setAuxDown(const Text &text) {
    FCITX_D();
    d->auxDown_ = text;
}

void InputPanel::setAuxUp(const Text &text) {
    FCITX_D();
    d->auxUp_ = text;
}

void InputPanel::setCandidateList(std::unique_ptr<CandidateList> candidate) {
    FCITX_D();
    d->candidate_ = std::move(candidate);
}

void InputPanel::setClientPreedit(const Text &clientPreedit) {
    FCITX_D();
    d->clientPreedit_ = clientPreedit;
}

void InputPanel::setPreedit(const Text &text) {
    FCITX_D();
    d->preedit_ = text;
}

const Text &InputPanel::auxDown() const {
    FCITX_D();
    return d->auxDown_;
}

const Text &InputPanel::auxUp() const {
    FCITX_D();
    return d->auxUp_;
}

const Text &InputPanel::clientPreedit() const {
    FCITX_D();
    return d->clientPreedit_;
}

const Text &InputPanel::preedit() const {
    FCITX_D();
    return d->preedit_;
}

void InputPanel::reset() {
    FCITX_D();
    d->preedit_.clear();
    d->clientPreedit_.clear();
    d->candidate_.reset();
    d->auxUp_.clear();
    d->auxDown_.clear();
}

bool InputPanel::empty() const {
    FCITX_D();
    return d->preedit_.size() == 0 && d->clientPreedit_.size() == 0 &&
           (!d->candidate_ || d->candidate_->size() == 0) &&
           d->auxUp_.size() == 0 && d->auxDown_.size() == 0;
}

CandidateList *InputPanel::candidateList() const {
    FCITX_D();
    return d->candidate_.get();
}
} // namespace fcitx
