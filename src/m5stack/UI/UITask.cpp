#include "m5stack/UI/UITask.h"

void updateUI(void *arg) {
    UITask *uiTask = static_cast<UITask *>(arg);
    while (true) {
        uiTask->update();
        delay(100);
    }
}

const char *UITask::TASK_NAME = "UITask";

UITask::UITask(TFT_eSPI *tft, const char *name, const char *version)
    : sprite(tft),
      title(name, version),
      btnA(UIButtonLabel::BUTTON_A_XPOS),
      btnB(UIButtonLabel::BUTTON_B_XPOS),
      btnC(UIButtonLabel::BUTTON_C_XPOS) {
    sprite.setColorDepth(8);
}

UITask::~UITask(void) {
}

void UITask::begin(BaseType_t core) {
    xTaskCreatePinnedToCore(updateUI, "UITask", 8192, this, 1, NULL, core);
}

void UITask::update(void) {
    this->title.draw(this->sprite);
    this->btnA.draw(this->sprite);
    this->btnB.draw(this->sprite);
    this->btnC.draw(this->sprite);
}

void UITask::setTitle(const char *name) {
    this->title.setTitle(name);
}

void UITask::setVersion(const char *version) {
    this->title.setVersion(version);
}

void UITask::setButtonA(const char *label) {
    this->btnA.setLabel(label);
}

void UITask::setButtonB(const char *label) {
    this->btnB.setLabel(label);
}

void UITask::setButtonC(const char *label) {
    this->btnC.setLabel(label);
}
