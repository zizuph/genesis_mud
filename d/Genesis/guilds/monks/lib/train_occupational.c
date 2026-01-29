/*
 * File:     train_occupational.c
 * Created:  Cirion, 1999.02.22
 * Purpose:  This object is just for use with skill decay ckecks.
 *           Training is handles in ~monks/lib/train.c and
 *           ~monks/room/room.c.
 * Modification Log:
 *
 */
#include "defs.h"
inherit MONK_LIB + "train";

void
create_object()
{
    ::create_object();
    mt_setup_skills_config(SS_OCCUP, m_indices(MONK_SKILL_CONFIG_MAPPING));
}


