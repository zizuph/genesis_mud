#define SPECIALS_DIR        "/d/Genesis/specials/"
#define DEBUGGER_DIR        (SPECIALS_DIR + "debugger/")

#define ABILITY_DIR         (SPECIALS_DIR + "new/")
#define ABILITIES_LIB       (ABILITY_DIR + "abilities")
#define TIMED_ABILITY_LIB   (ABILITY_DIR + "timed_ability")
#define ABILITY_LIB         (ABILITY_DIR + "ability")
#define COMBAT_ABILITY_LIB  (ABILITY_DIR + "combat_ability")
#define GUILD_MODIFIERS_LIB (ABILITY_DIR + "guild_modifiers")
#define TASK_MODIFIERS_LIB  (ABILITY_DIR + "task_modifiers")
#define EFFECT_OBJECT_LIB   (ABILITY_DIR + "effect_object")
#define TARGETTING_LIB      (ABILITY_DIR + "targetting")
#define COMPONENTS_LIB      (ABILITY_DIR + "components")
#define RESOURCE_LIB        (ABILITY_DIR + "resource")
#define RESIST_LIB          (ABILITY_DIR + "resist")
#define HOOKS_LIB           (ABILITY_DIR + "hooks")

#define MELEE_DIR           (ABILITY_DIR + "melee/")
#define DAMAGE_LIB          (MELEE_DIR + "damage")

#define MAGIC_DIR           (ABILITY_DIR + "magic/")
#define SPELL_LIB           (MAGIC_DIR + "spell")
#define SPELL_DIR           (MAGIC_DIR + "spells/")
#define SPELL_OBJ_DIR       (SPELL_DIR + "objs/")
#define SPELL_TARGETTING_LIB (MAGIC_DIR + "spell_targetting")
#define SPELL_EFFECT_LIB    (MAGIC_DIR + "spell_effect_object")
#define SPELL_HOOKS_LIB     (MAGIC_DIR + "spell_hooks")
#define SPELL_ENHANCER_LIB  (ABILITY_DIR + "lib/spell_enhancer")

#define PVP_DIR             (ABILITY_DIR + "pvp/")
#define SLOW_SH             (PVP_DIR + "slow_sh")

#define EFFECTS_DIR         (ABILITY_DIR + "effects/")
#define TIMED_MASTER_OBJ    (EFFECTS_DIR + "timed_master_obj")
#define DEBUFF_LIB          (EFFECTS_DIR + "debuff")
#define EFFECT_BASE_SH      (EFFECTS_DIR + "effect_base_sh")
#define EFFECT_BASE_OBJ     (EFFECTS_DIR + "effect_obj_base")

#define BOON_DIR            (EFFECTS_DIR + "boons/")
#define DAM_MOD_SH          (BOON_DIR + "dam_mod_sh")
#define DAM_MOD_OBJ_BASE    (BOON_DIR + "dam_mod_obj_base")
#define EVADE_SH            (BOON_DIR + "evade_sh")
#define EVADE_OBJ_BASE      (BOON_DIR + "evade_obj_base")
#define REFLECT_SH          (BOON_DIR + "reflect_sh")
#define REFLECT_OBJ_BASE    (BOON_DIR + "reflect_obj_base")

#define AILMENT_DIR         (EFFECTS_DIR + "ailments/")
#define STUN_SH             (AILMENT_DIR + "stun_sh")
#define STUN_OBJ_BASE       (AILMENT_DIR + "stun_obj_base")
#define WOUNDING_SH         (AILMENT_DIR + "wounding_sh")
#define WOUNDING_OBJ_BASE   (AILMENT_DIR + "wounding_obj_base")
#define INTERRUPT_SH        (AILMENT_DIR + "interrupt_sh")
#define INTERRUPT_OBJ_BASE  (AILMENT_DIR + "interrupt_obj_base")
#define BLIND_SH            (AILMENT_DIR + "blind_sh")
#define BLIND_OBJ_BASE      (AILMENT_DIR + "blind_obj_base")
#define DISABLE_ATTACK_SH   (AILMENT_DIR + "disable_attack_sh")
#define DISABLE_ATTACK_NPC_SH   (AILMENT_DIR + "disable_attack_npc_sh")
#define DISABLE_ATTACK_WEAPON_SH (AILMENT_DIR + "disable_attack_weapon_sh")
#define DISABLE_ATTACK_OBJ_BASE  (AILMENT_DIR + "disable_attack_obj_base")

// Spell class
#define SPELL_CLASS_0 0
#define SPELL_CLASS_1 1
#define SPELL_CLASS_2 2
#define SPELL_CLASS_3 3
#define SPELL_CLASS_4 4

// Component aid.  All spells should use COMPONENT_AID_NONE
// unless approval has been given for a higher level of aid.
// For componentless and long-lasting spells (5+ minutes)
#define COMPONENT_AID_NONE   1.0
// For spells that allow many casts (15+) per component.
#define COMPONENT_AID_LOW    1.1
// For spells that allow a few casts (<5) per component.
#define COMPONENT_AID_MEDIUM 1.2
// For high cost component spells (1 herb per cast instants,
// or 1 herb per cast effects that last < 30 seconds)
#define COMPONENT_AID_HIGH   1.3


// Default max spell effect durations in seconds by spell class
#define MAX_DURATION_CLASS_0 120
#define MAX_DURATION_CLASS_1 300
#define MAX_DURATION_CLASS_2 900    
#define MAX_DURATION_CLASS_3 1800
#define MAX_DURATION_CLASS_4 3600

// Spell duration capped by the spell class maximum, however
// duration may vary depending on variables such as spell power
#define MAX_SPELL_DURATION(class_max, var) set_dispel_time(min(class_max, var))

#define PVP_ABILITY_DISABLED 1
