inherit "/std/shadow";

#include "skillcache.h"

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

int bm_defense_active = 0;

void blademaster_set_defense_active() {
   bm_defense_active = 1;
}

void blademaster_set_defense_inactive() {
   bm_defense_active = 0;
}

int query_blademaster_defense_active() {
   return bm_defense_active;
}

varargs public mixed
hit_me(int pen, int dt, object attacker, int aid, int hitloc = -1)
{
   object member;
   int dt_hits = 0, hl_hits = 0, task_percent;
   int *valid_hitlocs = ({ });

   if(bm_defense_active) {
      if(hitloc == -1 && shadow_who->query_combat_object()) {
         valid_hitlocs = shadow_who->query_combat_object()->query_hitloc_id();
         if(sizeof(valid_hitlocs)) {
            hitloc = valid_hitlocs[random(sizeof(valid_hitlocs))-1];
         }
      }

      member = MEMBER_CACHE->get_member(shadow_who->query_real_name());
      dt_hits = member->query_dt_hits(dt) + 1;
      hl_hits = member->query_hl_hits(hitloc) + 1;

      if(MEMBER_CACHE->lock(shadow_who->query_real_name())) {
         member->add_dt_hit(dt);
         member->add_hl_hit(hitloc);
         MEMBER_CACHE->unlock(shadow_who->query_real_name());
      }
   }

   if(bm_defense_active) {
      task_percent = shadow_who->resolve_task(TASK_DIFFICULT,
                                 ({ TS_OCC, SS_WEP_SWORD, TS_STR, TS_DEX }),
                                 attacker, ({ SS_DEFENCE, TS_DEX, TS_DIS })
                     );

      if((task_percent + random(10) + MIN(MAX((hl_hits * 3 / 100), 30), 1)) > 50) {
         if(dt_hits > 10) {
            pen = MIN((pen - (random(3) + 1)), 1);
         }
      }
   }

   return shadow_who->hit_me(pen, dt, attacker, aid, hitloc);
}

void remove_bm_defense_shadow() {
   ::remove_shadow();
}
