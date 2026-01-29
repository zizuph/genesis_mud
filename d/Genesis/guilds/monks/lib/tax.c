/*
 * File:     tax.c
 * Created:  Cirion, 1998.08.05
 * Purpose:  Tax calculator for the Monks
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>

inherit MONKLIB;

#define TAXFILE MONK_DOC + "tax"

varargs void
dump_guild_skills(int type = SS_OCCUP, int tofile = 0)
{
    mixed     skills, mudlib_skill_data, monk_skill_data;
    int       i, index, mudlib_max, monk_max,
              total_mudlib, attack_interval,
              cround_interval, normal_pen, attack_penmod, stun_duration;
    string    mudlib_name, taxed, str;
    float     tax, total_tax, frequency, aid, skill_tax,
              strike_tax, plexus_tax, stun_chance;
    string    tax_file;

    str = "";
    total_tax = 0.0;
    total_mudlib = 0;

    if(type == SS_OCCUP)
    {
        tax_file = TAXFILE + "_occupational";
        index = 0;
    }
    else
    {
        tax_file = TAXFILE + "_layman";
        index = 1;
    }

    skills = m_indices(MONK_SKILL_CONFIG_MAPPING);
    skills = sort_array(skills);

    str += ("============================== SKILLS ==============================\n");
    str += (sprintf("%-20s%-10s%-15s%-10s%-10s\n", "Skill name", "Monk Max", "Mudlib Max", "Taxed?", "Tax"));
    str += ("====================================================================\n");

    for(i=0;i<sizeof(skills);i++)
    {
        mudlib_skill_data = SS_SKILL_DESC[skills[i]];

        monk_skill_data = MONK_SKILL_CONFIG_MAPPING[skills[i]][index];

        if(pointerp(mudlib_skill_data)) // non-taxed skill
        {
            mudlib_name = mudlib_skill_data[0];
            mudlib_max = mudlib_skill_data[4];

            if(skills[i] <= SS_MOUNTED_COMBAT)
            {
                taxed = "combat"; // combat-specific skills
                // combat skills are taxed at 1.5%
                tax = (itof(monk_skill_data[0] - mudlib_max) / 60.0) * 1.5;
                total_tax += tax;
            }
            else
            {
                taxed = "yes";
                tax = itof(monk_skill_data[0] - mudlib_max) / 60.0;
                total_tax += tax;
            }

            total_mudlib += monk_skill_data[0];
        }
        else
        {
            mudlib_name = monk_skill_data[1];
            mudlib_max = 0;
            taxed = "no";
            tax = 0.0;
        }

        monk_max = monk_skill_data[0];

        if(strlen(mudlib_name) > 15) // truncate too long skills
            mudlib_name = mudlib_name[0..14];

        str += (sprintf("%-24s%-10d%-10d%-10s%-10f\n", mudlib_name, monk_max, mudlib_max, taxed, tax));

    }

    str += ("====================================================================\n");
    str += ("Total mudlib skills: " + total_mudlib + "\n");
    str += ("Total skills tax: " + sprintf("%f", total_tax) + "\n");
    skill_tax = total_tax;
    str += ("====================================================================\n\n");

    str += ("============================== STRIKE ==============================\n");
    attack_interval = MONK_STRIKE_DELAY;
    cround_interval = 2;
    frequency = itof(cround_interval) / itof(attack_interval);
    normal_pen = F_PENMOD(40, 100);
    attack_penmod = F_MONK_STRIKE_PEN(100, 100); // pen with str=100, strike=100

    aid = frequency * (itof(normal_pen) / itof(attack_penmod));
    aid *= 100.0; // convert it into a percentage
    tax = aid / 6.0;

    str += ("Based on \"man guilds2\":\n");
 
    str += ("\"... a special attack hurting an opponent, which can be used every four ");
    str += ("combat rounds. The pen value depends on strength, and the guild stat is ");
    str += ("used as skill: F_PENMOD(str/4, guild_stat). For strength and guild stat of ");
    str += ("100, this gives 200. The best 'normal', ie non-magical weapons have a pen ");
    str += ("value of 40: F_PENMOD(40, 100) = 280. Thus the combat aid is 18%  ");
    str += ("(25% * 200/280).\"\n\n");

    str += ("Time between strike attacks:         " + attack_interval + "\n");
    str += ("Combat round interval:               " + cround_interval + "\n");
    str += ("Best normal weapon penmod:           " + normal_pen + "\n");
    str += ("Strike penmod (str=100, strike=100): " + attack_penmod + "\n");
    str += ("Attack aid:                          " + sprintf("%f", aid) + "%\n");
    str += ("Tax:                                 " + sprintf("%f", tax) + "\n");

    tax /= 2.0; // tax reduction for having a special-specific skills
    strike_tax = tax;
    total_tax += tax;

    str += ("Tax reduction for a required skill:  " + sprintf("%f", tax) + "\n");

    str += ("====================================================================\n\n");

    if(type == SS_OCCUP) // plexus is only for occupational members
    {
        attack_interval = MONK_PLEXUS_STUN_MIN_INTERVAL;
        cround_interval = 2;
        frequency = itof(cround_interval) / itof(attack_interval);
        stun_duration = F_MONK_PLEXUS_STUN_DURATION(100, 100, 60);
        stun_chance = 0.5;

        aid = (itof(stun_duration) / itof(attack_interval)) * stun_chance;

        aid *= 100.0; // convert it into a percentage
        tax = aid / 6.0;
        total_tax += tax;

        str += ("============================== PLEXUS ==============================\n");
        str += ("Based on \"man guilds2\":\n");
        str += ("\"Let us assume a special attack which disables an opponent for three combat ");
        str += ("rounds. The special attack can be used every ten combat rounds, with a ");
        str += ("probablity of success of 50%. Thus, you would have a combat aid of about ");
        str += ("15% (3/10 * 50%).\"\n\n");

        str += ("Time between plexus attacks:         " + attack_interval + "\n");
        str += ("Combat round interval:               " + cround_interval + "\n");
        str += ("Stun duration (str=100,plexus=100,\n");
        str += ("       enemy ac=60):                 " + stun_duration + "\n");
        str += ("Stun success chance:                 " + sprintf("%f", stun_chance * 100.0) + "%\n");
        str += ("Attack aid:                          " + sprintf("%f", aid) + "%\n");
        str += ("Tax:                                 " + sprintf("%f", tax) + "\n");


        str += ("====================================================================\n\n");
    }

    str += ("TOTAL TAX: " + sprintf("%f", total_tax) + "%\n");
    str += ("This information generated on " + ctime(time()) + ".\n");
    str += ("====================================================================\n\n");

    write (str);

    // write it all to a file, if we specified to do so
    if(tofile)
    {
        seteuid(getuid(this_object()));

        // backup the old one
        if(file_size(tax_file + ".old") > 0)
            rm(tax_file + ".old");

        if(file_size(tax_file) > 0)
            rename(tax_file, tax_file + ".old");

        // write it out to a file
        write_file(tax_file, str);

        write("(output saved to " + tax_file + ")\n");
    }
}


