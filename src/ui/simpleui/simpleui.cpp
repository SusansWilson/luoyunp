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

#include "simpleui.h"
#include "fcitx/action.h"
#include "fcitx/addonfactory.h"
#include "fcitx/addonmanager.h"
#include "fcitx/candidatelist.h"
#include "fcitx/inputcontext.h"
#include "fcitx/inputpanel.h"
#include "fcitx/statusarea.h"
#include <iostream>

namespace fcitx {

SimpleUI::SimpleUI(Instance *instance) : instance_(instance) {}

SimpleUI::~SimpleUI() {}

void SimpleUI::resume() { suspended_ = false; }

void SimpleUI::suspend() { suspended_ = true; }

void SimpleUI::update(UserInterfaceComponent component,
                      InputContext *inputContext) {
    switch (component) {
    case UserInterfaceComponent::StatusArea:
        printStatusArea(inputContext);
        break;
    case UserInterfaceComponent::InputPanel:
        printInputPanel(inputContext);
        break;
    }
}

void SimpleUI::printStatusArea(InputContext *inputContext) {
    auto &statusArea = inputContext->statusArea();
    for (auto group : {StatusGroup::BeforeInputMethod, StatusGroup::InputMethod,
                       StatusGroup::AfterInputMethod}) {
        for (auto action : statusArea.actions(group)) {
            std::cout << "Action: " << action->name() << std::endl;
            std::cout << "Text: " << action->shortText(inputContext)
                      << std::endl;
            std::cout << "Icon: " << action->icon(inputContext) << std::endl;
        }
    }
}

void SimpleUI::printInputPanel(InputContext *inputContext) {
    auto &inputPanel = inputContext->inputPanel();
    auto preedit = instance_->outputFilter(inputContext, inputPanel.preedit());
    auto preeditString = preedit.toString();
    auto auxUp = instance_->outputFilter(inputContext, inputPanel.auxUp());
    auto auxDown = instance_->outputFilter(inputContext, inputPanel.auxDown());
    auto cursor = preedit.cursor();
    if (cursor >= 0) {
        preeditString.insert(cursor, "|");
    }
    std::cerr << "Preedit: " << preeditString << std::endl;
    std::cerr << "AuxUp: " << auxUp.toString() << std::endl;
    std::cerr << "AuxDown: " << auxDown.toString() << std::endl;
    std::cerr << "Candidates: " << std::endl;
    if (auto candidateList = inputPanel.candidateList()) {
        for (int i = 0; i < candidateList->size(); i++) {
            auto label =
                instance_->outputFilter(inputContext, candidateList->label(i));
            auto candidate = instance_->outputFilter(
                inputContext, candidateList->candidate(i).text());
            std::cerr << label.toString() << " " << candidate.toString()
                      << std::endl;
        }
    }
}

class SimpleUIFactory : public AddonFactory {
public:
    AddonInstance *create(AddonManager *manager) override {
        return new SimpleUI(manager->instance());
    }
};
} // namespace fcitx

FCITX_ADDON_FACTORY(fcitx::SimpleUIFactory);
