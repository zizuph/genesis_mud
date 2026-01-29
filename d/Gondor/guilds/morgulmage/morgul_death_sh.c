/*
 *  /d/Gondor/guilds/morgulmage/morgul_corpse_sh.c
 *
 *  This is a shadow responsible for creating a distinctive, morgul
 *  corpse when a death is caused by one of the morgul spells.
 *  Concept and implementation by Chmee.
 */
inherit "/std/shadow";

#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"
#include <stdproperties.h>

public nomask void set_death_cause( int cause );
public nomask void set_death_variant( int variant );
public nomask void set_no_corpse( int flag );

int _death_cause, _death_variant, _no_corpse_flag;

public object make_corpse()
{
 int size;
 object corpse;
                                /*First let us check if the creator of the
                                 *victim didn't prepare his/her own mask of
                                 *the make_corpse() function.             */
    if (objectp(corpse = (object)query_shadow_who()->make_corpse()))
    {
        return corpse;
    }

    if (!_no_corpse_flag)
    {
        corpse = clone_object( MORGUL_CORPSE );
        size = query_shadow_who()->query_prop( OBJ_I_VOLUME );
        if (size < 2000)
        {
            corpse->set_corpse_size( SMALL_CS );
        }
        else if (size < 100000)
        {
            corpse->set_corpse_size( MEDIUM_CS );
        }
        else
        {
            corpse->set_corpse_size( LARGE_CS );
        }
        corpse->set_death_cause( _death_cause );
        corpse->set_death_variant( _death_variant );
        corpse->set_name( query_shadow_who()->query_name() );
        corpse->add_prop( CONT_I_WEIGHT,
            query_shadow_who()->query_prop( CONT_I_WEIGHT ) );
        corpse->add_prop( CONT_I_VOLUME,
            query_shadow_who()->query_prop( CONT_I_VOLUME ) );
        corpse->add_prop( CONT_I_MAX_WEIGHT,
            query_shadow_who()->query_prop( CONT_I_MAX_WEIGHT ) );
        corpse->add_prop( CONT_I_MAX_VOLUME,
            query_shadow_who()->query_prop( CONT_I_MAX_VOLUME ) );
        corpse->add_prop( CORPSE_S_RACE,
            query_shadow_who()->query_race_name() );
        corpse->add_prop( CONT_I_TRANSP, 1 );
                                /*I may want to modify the leftovers later*/
        corpse->set_leftover_list( query_shadow_who()->query_leftover() );
        return corpse;
    }
}

public nomask void set_death_cause( int cause )
{
    _death_cause = cause;
}

public nomask void set_death_variant( int variant )
{
    _death_variant = variant;
}

/* Function    : set_no_corpse
 * Descriptions: When you have a corpse then a bunch or procedures
 *               is executed. It's no need to do that if a death
 *               variant doesn't leave a corpse.
 * Arguments   : 1 if there is no corpse yet, 0 otherwise (default).
 */
public nomask void set_no_corpse( int flag = 0 )
{
    _no_corpse_flag = flag;
}
