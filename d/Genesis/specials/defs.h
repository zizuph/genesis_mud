#define ABILITY_DIR         "/d/Genesis/specials/"
#define ABILITIES_LIB       (ABILITY_DIR + "abilities")
#define TIMED_ABILITY_LIB   (ABILITY_DIR + "timed_ability")
#define ABILITY_LIB         (ABILITY_DIR + "ability")
#define HOOKS_LIB           (ABILITY_DIR + "hooks")
#define TARGETTING_LIB      (ABILITY_DIR + "targetting")
#define ABILITY_STD_DIR     (ABILITY_DIR + "std/")
#define STD_SPELLS_DIR      (ABILITY_STD_DIR + "spells/")
#define STD_SPELL_OBJ_DIR   (STD_SPELLS_DIR + "obj/")

#define DEBUFF_LIB          (ABILITY_STD_DIR + "debuff")
#define DAMAGE_LIB          (ABILITY_STD_DIR + "damage")
#define COMBAT_BASE_LIB     (ABILITY_STD_DIR + "combat_special_base")
#define EFFECT_OBJECT_LIB   (ABILITY_DIR + "effect_object")
#define TASK_MODIFIERS_LIB  (ABILITY_STD_DIR + "task_modifiers")
#define GUILD_MODIFIERS_LIB (ABILITY_STD_DIR + "guild_modifiers")
#define EFFECT_BASE_SH      (ABILITY_STD_DIR + "effect_base_sh")
#define EFFECT_BASE_OBJ     (ABILITY_STD_DIR + "effect_obj_base")
#define EVADE_SH            (ABILITY_STD_DIR + "evade_sh")
#define EVADE_OBJ_BASE      (ABILITY_STD_DIR + "evade_obj_base")

#define STUN_SH             (ABILITY_STD_DIR + "stun_sh")
#define STUN_OBJ_BASE       (ABILITY_STD_DIR + "stun_obj_base")

#define WOUNDING_SH         (ABILITY_STD_DIR + "wounding_sh")
#define WOUNDING_OBJ_BASE   (ABILITY_STD_DIR + "wounding_obj_base")

#define REFLECT_SH          (ABILITY_STD_DIR + "reflect_sh")
#define REFLECT_OBJ_BASE    (ABILITY_STD_DIR + "reflect_obj_base")

#define INTERRUPT_SH        (ABILITY_STD_DIR + "interrupt_sh")
#define INTERRUPT_OBJ_BASE  (ABILITY_STD_DIR + "interrupt_obj_base")

#define BLIND_SH            (ABILITY_STD_DIR + "blind_sh")
#define BLIND_OBJ_BASE      (ABILITY_STD_DIR + "blind_obj_base")

#define DEBUGGER_DIR        (ABILITY_DIR + "debugger/")

#define PVP_ABILITY_DISABLED 1

#define INTOX_MOD 50

#define SPELLCRAFT_MOD 75

#define F_DYNAMIC_SPELL_COST(stat)  \
    (3 + ((stat) * (100 - (INTOX_MOD) / 2) * SPELLCRAFT_MOD) / 50000)
