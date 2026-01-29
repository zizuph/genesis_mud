/*
 * Hammerhands formulae
 * TAPAKAH, 03/2006
 */

#ifndef HH_FORMULAS
#define HH_FORMULAS

#define HH_F_SCALE 2000
#define HH_F_SCALE_SKILL(sl) (sl/HH_F_SCALE)
#define HH_F_JAB_HIT(wepskill,enemydex, str,enemyparry,enemydef,jabskill) \
   ((wepskill - 65) +    \
    (200 - enemydex) +   \
    (str - enemyparry) + \
    (100 - enemydef) +   \
    jabskill)

#define HH_JAB_DAMAGE(jabskill,str,whit,wpen,hitlocval) \
   (((jabskill*2) + \
     str +          \
     whit +         \
     wpen) / 8 / (hitlocval/10+1) + 1)

#define HH_F_HOOK_HIT(wepskill,enemydex,mydex,enemyparry,enemydef,wepweight,hookskill) \
  ((wepskill - 75)*2 +            \
   (170 - enemydex) +             \
   (mydex - 2*enemydef) +         \
   (wepweight/200 - enemyparry) + \
   hookskill)

#define HH_F_HOOK_DAMAGE(hookskill,wpen,wepweight,hitlocval) \
  (((hookskill*2)   + \
    (wpen*2)        + \
    (wepweight/200)) / 6 / (hitlocval/8+1) + 1)

#endif      
     
