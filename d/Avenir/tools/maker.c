/*
 * File:     room_maintenance
 * Created:  Cirion, 1990.03.13
 * Purpose:  tool to facilitate quick creation of simple objects
 * Modification Log:
 *
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>    /* MASTER_OB, etc      */
#include <cmdparse.h>  /* FIND_STR_IN_OBJECT  */

inherit "/cmd/std/tracer_tool_base";

#define TRUE_VALUE      "true"
#define INDENT          "    "
#define QUOTE           "\""

string *sort_priorities = ({ "name", "short", "long", "adj" });

string
get_soul_id()
{
    return "Cirion's Object Maker";
}

int
query_tool_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    return ([
           "make" : "make",
          ]);
}


mapping
parse_command_flags(string str)
{
    string      *parts;
    mapping     mp = ([]);
    int         i;
    string      key;
    string      value;
    string      *args;
    string      part;

    if(!strlen(str))
        return mp;

    // if no "-type" is specified, prepend it.
    if(str[0] != '-')
        str = "-type " + str;

    str  = " " + str;
    parts = explode(str, " -");
    parts -= ({ "" });

    for(i=0;i<sizeof(parts);i++)
    {
        part = parts[i];

        if(!strlen(part))
            continue;

        args = explode(part, " ");
        args -= ({ "" });


        // unqualified args default to "true"
        if(sizeof(args) == 1)
        {
            key = part;
            value = TRUE_VALUE;
        }
        else
        {
            key = args[0];
            args = exclude_array(args, 0, 0); // get rid of first element
            value = implode(args, " "); // reconstruct remainder of command

        }

        mp += ([ key : value ]);
    }

    return mp;
}


object
check_object(mapping properties)
{
    string      object_type;
    string      check_file;

    object_type = properties["type"];
    check_file = "/std/" + object_type + ".c";

    if(file_size(check_file) <= 0)
    {
        notify_fail("Error: file: " + check_file + " does not exist\n");
        return 0;
    }

    return find_object(check_file);
}

mapping
validate_properties(mapping properties)
{
    string      str;

    // make sure the "set_long" ends with \n
    if((str = properties["long"]) && (!wildmatch("*\\n", str)))
        properties["long"] = str + "\\n";

    if((str = properties["long"]) && (str[0..0] != QUOTE))
        properties["long"] = QUOTE + str + QUOTE;



    // enquote things that may or may not be enquoted
    if((str = properties["short"]) && (str[0..0] != QUOTE))
        properties["short"] = QUOTE + str + QUOTE;

    // enquote things that may or may not be enquoted
    if((str = properties["pshort"]) && (str[0..0] != QUOTE))
        properties["pshort"] = QUOTE + str + QUOTE;

    // need to also make sure we are not setting an array
    if((str = properties["adj"]) && (str[0..0] != QUOTE) && (str[0..0] != "("))
        properties["adj"] = QUOTE + str + QUOTE;

    if((str = properties["name"]) && (str[0..0] != QUOTE) && (str[0..0] != "("))
        properties["name"] = QUOTE + str + QUOTE;

    if((str = properties["pname"]) && (str[0..0] != QUOTE) && (str[0..0] != "("))
        properties["pname"] = QUOTE + str + QUOTE;

    // insert other valdations here....

    return properties;
}

string
header_string()
{
    string  str;

    str = "";
    str += "// Auto-generated object file\n";
    str += "// Created using " + get_soul_id() + "\n";
    str += "//    (" + file_name(this_object()) + ")\n";
    str += "// Executed by: " + this_player()->query_name()
        + " on " + ctime(time()) + "\n";
    str += "#include <stdproperties.h>\n";
    str += "#include <wa_types.h>\n";
    str += "#include <formulas.h>\n";

    return str;
}

int
function_order(string arg1, string arg2)
{
    int     pos1;
    int     pos2;

    // we want to put "set_name()" before "set_long()", etc.
    pos1 = member_array(arg1, sort_priorities);
    pos2 = member_array(arg2, sort_priorities);

    if(pos1 > pos2)
        return 1;
    else if(pos2 > pos1)
        return -1;
    else
        return 0;
}

string
extra_code(mapping props)
{
    string  type;
    string  code = "";

    code += "\n";

    type = props["type"];

    if(type == "weapon")
    {
        //code += INDENT + "set_default_weapon();\n";
        code += INDENT + "add_prop(OBJ_I_WEIGHT, "
            + "F_WEIGHT_DEFAULT_WEAPON(query_pen(), query_wt()));\n";
        code += INDENT + "add_prop(OBJ_I_VALUE, "
            + "F_VALUE_WEAPON(query_hit(), query_pen()));\n";
    }

    if(type == "armour")
    {
        //code += INDENT + INDENT + "set_default_armour();\n";
        code += INDENT + "add_prop(OBJ_I_WEIGHT, "
            + "F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));\n";
        code += INDENT + "add_prop(OBJ_I_VALUE, "
            + "F_VALUE_WEAPON(query_ac()));\n";
    }

    code += "\n";

    return code;

}

int
create_code(mapping properties)
{
    object      ob;
    string      file;
    string      code = "";
    int         i;
    string      *indices;
    string      funcname;
    string      value;

    // fill in any defaults, etc.
    properties = validate_properties(properties);

    // verify if is a valid object
    if(!(ob = check_object(properties)))
        return 0;

    if(file = properties["file"])
        properties = m_delete(properties, "file");
    else
        file = "test_" + properties["type"];

    // qualify pathname for partly qualified paths
    if(!wildmatch("/*", file))
        file = this_player()->query_path() + "/" + file;

    // append a .c to the end
    if(!wildmatch("*.c", file))
        file += ".c";

    // don't overwrite existing files
    if(file_size(file) > 0)
    {
        notify_fail("Error: " + file + " already exists.\n");
        return 0;
    }

    if(!write_file(file, header_string()))
    {
        notify_fail("Error: could not write to file: " + file + "\n");
        return 0;
    }

    // inherit the correct type
    code += "inherit \"/std/" + properties["type"] + "\";\n\n";

    code += "void\n";
    code += "create_" + properties["type"] + "()\n";
    code += "{\n";

    indices = m_indices(properties);
    indices = sort_array(indices, function_order);

    for(i = 0; i < sizeof(indices); i++)
    {
        funcname = "set_" + indices[i];
        if(!function_exists(funcname, ob))
        {
            write("Warning: function: " + funcname + " does not exist "
                + "in " + file_name(ob) + ". Skipping...\n");
            continue;
        }

        value = properties[indices[i]];

        // if it is a quote string, it may be long (e.g., in the
        // set_long() function). Break it up if necessary.
        if(value[0 .. 0] == QUOTE)
        {
            // indent and re-quote
            value = break_string(properties[indices[i]], 40);
            value = implode(explode(value, "\n"), QUOTE + "\n" + "        + " + QUOTE + " ");
        }

        // add it to the code.
        code += INDENT + funcname + "("
            + value
            + ");\n";

    }

    code += extra_code(properties);

    code += "}\n";

    if(!write_file(file, code))
    {
        notify_fail("Error: could not write to file: " + file + "\n");
        return 0;
    }

    write("Successfully wrote to: " + file + "\n");

    if(catch(file->teleldensanka()))
        write("Error loading file\n");
    else
        write("Successfully loaded file.\n");

    return 1;
}

int
make(string str)
{
    mapping properties;

    notify_fail("Usage: " + query_verb() + " -flag value\n"
        + "For example: " + query_verb() + " weapon -file mysword -short heavy iron sword "
        + "-long It is a godd sword. -adj ({ \"heavy\", \"iron\" }) "
        + "-dt W_IMPALE | W_SLASH -wt W_SWORD\n");

    if(!strlen(str))
        return 0;

    properties = parse_command_flags(str);

    if(!properties)
        return 0;

    if(!create_code(properties))
        return 0;

    return 1;
}

