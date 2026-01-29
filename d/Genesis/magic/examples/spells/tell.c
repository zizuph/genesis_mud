inherit "/d/Genesis/magic/spells/tell";

#include <options.h>

public object *
find_tell_targets(object caster, string name)
{
    return tell_target_one_distant_guild_member_or_known_living(caster,
        name, "Caster's guilld name");
}

public void
tell(object caster, object *targets, int *resist, int result)
{
    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_tell("You tell " +  targets[0]->query_met_name() +
            ": " + query_tell_message() + "\n");
    }

    targets[0]->catch_tell("A vision of " + caster->query_met_name() + 
        " appears to you and tells you: " + query_tell_message() + "\n");
}        
