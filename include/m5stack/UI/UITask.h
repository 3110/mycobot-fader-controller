#ifndef _UI_TASK_H
#define _UI_TASK_H

#include "UI.h"
#include "UIButtonLabel.h"
#include "UITitle.h"

class UITask {
public:
    UITask(TFT_eSPI *tft, const char *name, const char *version);
    virtual ~UITask(void);

    virtual void begin(BaseType_t core);
    virtual void update(void);

    virtual void setTitle(const char *name);
    virtual void setVersion(const char *version);
    virtual void setButtonA(const char *label);
    virtual void setButtonB(const char *label);
    virtual void setButtonC(const char *label);

protected:
    TFT_eSprite sprite;

private:
    static const char *TASK_NAME;

    UITitle title;
    UIButtonLabel btnA;
    UIButtonLabel btnB;
    UIButtonLabel btnC;
};

#endif