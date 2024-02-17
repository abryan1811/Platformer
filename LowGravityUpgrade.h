#ifndef LOW_GRAVITY_UPGRADE_H
#define LOW_GRAVITY_UPGRADE_H

#include "Upgrade.h"
#include "Character.h"

class LowGravityUpgrade : public Upgrade {
public:
     LowGravityUpgrade(float x, float y, Color color);

    virtual void ApplyEffect(Character& character) override;
};

#endif // LOW_GRAVITY_UPGRADE_H
