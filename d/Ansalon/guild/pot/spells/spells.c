/* Stralle @ Genesis 010619
 *
 * Keeps track of the spells PoT has.
 * Update this object in order for the spells to be updated in
 * the medallion
 */

#pragma strict_types

#include "../spells.h"
#include "../guild.h"
#include "../admin/admin.h"
#include "/d/Ansalon/common/defs.h"

static mixed *m_spell_list = SPELL_LIST;

mixed *
query_spell_list()
{
    return m_spell_list;
}

int
set_spells(object priest)
{
    int spells = 0, ret = 0;

    if (priest->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    if (GUILD_ADMIN->query_priest_has_punishment(priest->query_real_name(),
        P_SPELLS_RESTRICTED) || !priest->has_allowed_priest_alignment())
    {
        return SPELLS_REVOKED;
    }

    switch (priest->query_skill(PS_GUILD_LEVEL) / 10 + 1)
    {
        /* Intentional break throughs all over */

        /* High Priest */
        case 15:
        case 14:
        case 13:
            spells += PPLANESWALK_ID;
        case 12:
            spells += PPAIN_ID;
        case 11:
            spells += PGEM_ID;

        /* Priest */
        case 10:
            spells += PRESTORE_ID;
        case 9:
            spells += PBLESS_ID;
            spells += PSCRY_ID;
        case 8:
            spells += PBLIND_ID;
            spells += PTALON_ID;
        case 7:
            spells += PIDENTIFY_ID;
            spells += PHAMMER_ID;
            spells += PIMPRECATE_ID;
        case 6:
            spells += PMIRAGE_ID;
            spells += PDRAIN_ID;

        /* Cleric */
        case 5:
            spells += PSLOW_ID;
            spells += PEYES_ID;
        case 4:
            if (GUILD_ADMIN->query_priest_has_quest(priest->query_real_name(),
                Q_VERMINAARD))
                spells += PHEAL_ID;
            spells += PHEARING_ID;
        case 3:
            spells += PCURSE_ID;
        case 2:
            if (GUILD_ADMIN->query_priest_has_quest(priest->query_real_name(),
                Q_KALAMAN))
                spells += PALIGN_ID;
        case 1:
            spells += PTELL_ID;
    }
    
    if ((~priest->query_skill(PS_SPELLS)) & spells)
    {
        priest->set_skill(PS_SPELLS, priest->query_skill(PS_SPELLS) | spells);
        ret |= NEW_SPELLS;
    }
    
    if (priest->query_prop(POT_GOT_NEW_SPELL))
    {
        priest->set_skill(PS_SPELLS, priest->query_skill(PS_SPELLS) |
            priest->query_prop(POT_GOT_NEW_SPELL)[1]);
        ret |= GOT_SPELL;
    }
    
    P(MEDALLION_ID, priest)->update_spells();
    return ret | SPELLS_UPDATED;
}
