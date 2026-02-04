
#include <math.h>
#include "../voptions.h"
#include "../guild.h"

// Prototypes
varargs int set_vamp_option(int opt, int on, int save = 1);
int query_vamp_option(int opt);

// Variables
public object query_manager();
static int options = 0;

void update_vamp_drain_option(int opt, int on)
{
    object drain_obj;
    int * drain_options = ({ VOPT_DRAIN_SKILL_MODE,
                             VOPT_DRAIN_RESIST_MODE,
                             VOPT_DRAIN_HASTE_MODE });
    
    drain_options -= ({ opt });
    
    if (on)
    {
        foreach (int doption : drain_options)
        {            
            set_vamp_option(doption, 0);
        }
        if (objectp(drain_obj = present("_hidden_vamp_drain_object", QSW)))
        {
            drain_obj->set_drain_mode(MATH_FIND_EXP(opt) - 14);
        }
    }
    else
    {
        int has_true = 0;
        foreach (int doption : drain_options)
        {
            has_true = has_true || query_vamp_option(doption);
        }
        
        if (!has_true)
        {
            // At least one options must be true. We don't allow it to be set
            // to false if all other options are true.
            set_vamp_option(opt, 1);
        }
    }
}

void update_vamp_option(int opt, int on)
{
    object drain_obj;
    
    switch (opt)
    {
    case VOPT_VSAY:
        if (on)
	    {
            setuid();
            seteuid(getuid());
            clone_object(OBJ_DIR + "vsay_ob")->move(QSW, 1);
	    }
        else
	    {
            deep_inventory(QSW)->remove_vsay_ob();
    	}
        break;
    
    case VOPT_DRAIN_SKILL_MODE:
    case VOPT_DRAIN_RESIST_MODE:
    case VOPT_DRAIN_HASTE_MODE:
        update_vamp_drain_option(opt, on);
        break;
    }
}

varargs int set_vamp_option(int opt, int on, int save = 1)
{
    if (on)
    {
        if (options & opt)
        {
            return 0;
        }

        options |= opt;
    }
    else
    {
        if (!(options & opt))
        {
            return 0;
        }

        options ^= opt;
    }

    update_vamp_option(opt, on);

    if (save)
    {
        query_manager()->set_options(QSW, options);
    }

    return 1;
}

int query_vamp_option(int opt)
{
    return (options & opt);
}

int query_vamp_options()
{
    return options;
}
    
void init_vamp_options()
{
    options = query_manager()->query_options(QSW);
    
    if (query_vamp_option(VOPT_VSAY))
    {
        update_vamp_option(VOPT_VSAY, 1);
    }
    if (query_vamp_option(VOPT_VAMPIRE_RACE))
    {
        update_vamp_option(VOPT_VAMPIRE_RACE, 1);
    }

    // Set up the proper drain mode
    if (query_vamp_option(VOPT_DRAIN_RESIST_MODE))
    {
        update_vamp_option(VOPT_DRAIN_RESIST_MODE, 1);
    }
    else if (query_vamp_option(VOPT_DRAIN_HASTE_MODE))
    {
        update_vamp_option(VOPT_DRAIN_HASTE_MODE, 1);
    }
    else
    {
        set_vamp_option(VOPT_DRAIN_SKILL_MODE, 1);
    }
}

