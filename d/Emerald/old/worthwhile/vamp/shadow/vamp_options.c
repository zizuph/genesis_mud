#include "../voptions.h"
#include "../guild.h"

#define SW shadow_who
#define ALWAYS_NOTIFY_THIRST

static int options = 0;

void update_vamp_option(int opt, int on)
{
    if (opt == VOPT_NOTIFY_THIRST)
    {
        if (on)
        {
            THIRST_NOTIFIER->register(SW);
        }
        else
        {
            THIRST_NOTIFIER->unregister(SW);
        }
    }
    else if (opt == VOPT_VSAY)
    {
        if (on)
	{
            setuid();
            seteuid(getuid());
            clone_object(VAMP_OBJ_DIR + "vsay_ob")->move(SW, 1);
	}
        else
	{
            deep_inventory(SW)->remove_vsay_ob();
	}
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
        MANAGER->set_options(SW, options);
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
    options = MANAGER->query_options(SW);

#ifndef ALWAYS_NOTIFY_THIRST
    if (query_vamp_option(VOPT_NOTIFY_THIRST))
#else
    if (!SW->query_wiz_level() || query_vamp_option(VOPT_NOTIFY_THIRST))
#endif
    {
        update_vamp_option(VOPT_NOTIFY_THIRST, 1);
    }
    
    if (query_vamp_option(VOPT_VSAY))
    {
        update_vamp_option(VOPT_VSAY, 1);
    }
}
