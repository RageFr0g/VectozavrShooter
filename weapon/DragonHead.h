

#ifndef SHOOTER_DRAGONHEAD_H
#define SHOOTER_DRAGONHEAD_H

#include "Weapon.h"
#include "../engine/utils/ResourceManager.h"
#include "../ShooterConsts.h"
#include "../engine/animation/Animations.h"


class DragonHead final : public Weapon {
public:
    explicit DragonHead() : Weapon(100, 100, 3, 0.04, 5, 3.0,
        ShooterConsts::DRAGON_FIRE_SOUND, ShooterConsts::DRAGON_RELOAD_SOUND, ObjectNameTag("dragon_head"),
        ShooterConsts::DRAGON_OBJ, Vec3D{ 3, 3, 3 },
        Vec3D{ -2.2, 1.0, 2.0 }, Vec3D{ 0, 0, 0 }) {}
    
    std::map<ObjectNameTag, double>
        fireABullet(std::function<IntersectionInformation(const Vec3D&, const Vec3D&)> rayCastFunction,
            const Vec3D& cameraPosition, const Vec3D& direction) const {
        std::map<ObjectNameTag, double> damagedPlayers;
        double spreading = _spreading * ShooterConsts::FIRE_DISTANCE / 100.0;

        //generate random vector
        Vec3D randV(spreading * (1.0 - 2.0 * static_cast<double>(rand()) / RAND_MAX),
            spreading * (1.0 - 2.0 * static_cast<double>(rand()) / RAND_MAX),
            spreading * (1.0 - 2.0 * static_cast<double>(rand()) / RAND_MAX));

        // damage player
        auto rayCast = rayCastFunction(cameraPosition, cameraPosition + direction * 3 + randV / 100);
        Vec3D lineFrom = position() + model() * Vec3D(triangles().back()[0]);
        Vec3D lineTo = position() + direction * 5;

        if (rayCast.distanceToObject < 3) {
            lineTo = rayCast.pointOfIntersection;
            if (rayCast.objectName.contains(ObjectNameTag("Enemy"))) {

                damagedPlayers[rayCast.objectName] += _damage / (1.0 + rayCast.distanceToObject);

                // If you hit the head the damage will be doubled
              /*  if (rayCast.objectName.contains(ObjectNameTag("head"))) {
                    damagedPlayers[rayCast.objectName] += _damage / (1.0 + rayCast.distanceToObject);
                }
                // If you hit the foot the damage will be divided by 2
                if (rayCast.objectName.contains(ObjectNameTag("foot"))) {
                    damagedPlayers[rayCast.objectName] -= 0.5 * _damage / (1.0 + rayCast.distanceToObject);
                }*/

            }
            _addTraceCallBack(lineFrom, lineTo);
        }
        // add trace line
         
         
       
       return damagedPlayers;
         
    }
};


#endif //SHOOTER_3DZAVR_GUN_H
