/*
 * Adapted from AlsoNotMehh's AzerothCore PR #27858.
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "AreaDefines.h"
#include "DBCStores.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "GameObjectScript.h"

class go_mod_direbrew_anti_block : public GameObjectScript
{
public:
    go_mod_direbrew_anti_block() : GameObjectScript("go_mod_direbrew_anti_block") { }

    struct go_mod_direbrew_anti_blockAI : public GameObjectAI
    {
        explicit go_mod_direbrew_anti_blockAI(GameObject* gameObject) : GameObjectAI(gameObject) { }

        void UpdateAI(uint32 /*diff*/) override
        {
            if (_initialized)
                return;

            _initialized = true;

            // Preserve the stock SmartAI's one-time ready-state initialization.
            me->SetGoState(GO_STATE_READY);

            uint32 zoneId = 0;
            uint32 areaId = 0;
            me->GetZoneAndAreaId(zoneId, areaId);

            AreaTableEntry const* zone = sAreaTableStore.LookupEntry(zoneId);
            AreaTableEntry const* area = sAreaTableStore.LookupEntry(areaId);

            if ((area && (area->flags & (AREA_FLAG_SANCTUARY | AREA_FLAG_CAPITAL))) ||
                (zone && (zone->flags & (AREA_FLAG_SANCTUARY | AREA_FLAG_CAPITAL))))
                me->EnableCollision(false);
        }

    private:
        bool _initialized = false;
    };

    GameObjectAI* GetAI(GameObject* gameObject) const override
    {
        return new go_mod_direbrew_anti_blockAI(gameObject);
    }
};

void Addmod_direbrew_anti_blockScripts()
{
    new go_mod_direbrew_anti_block();
}
