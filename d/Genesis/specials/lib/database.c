/* 
 * Database Table Object
 *  
 * This is a pretty crude implementation of a database table with
 * variable number of columns. The idea is that someone can query
 * the table and it will return all rows, or they can filter it
 * and get back particular rows. 
 *
 * Created by Petros, March 2009
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public string * m_keys; // list of columns that comprise the key
public string * m_columns; // list of columns in the table
public mixed  * m_rows; // list of rows in the table

// Prototypes
public mixed *  query_rows(mapping conditions);
public int      add_column(string column, int required = 0);
public void     reset_row_ids();

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return FILE_PATH(MASTER_OB(this_object())) + "database";
}

/*
 * Function:    save_data
 * Description: Call this to persist the data into a file.
 */
public void
save_data()
{
    string datafile;
    
    datafile = query_database_file();
    if (!strlen(datafile)
        || (!sizeof(m_rows) && !sizeof(m_columns)))
    {
        return;
    }

    // Set the id information to access the filesystem
    setuid();
    seteuid(getuid());

    if (sizeof(m_columns) == 1 && sizeof(m_rows) == 0
        && file_size(datafile + ".o") <= 0)
    {
        // If there's nothing in the database, and we haven't already
        // created the file, then don't create it.
        return;
    }
    
    save_map( ([ 
                    "rows"      : m_rows,
                    "columns"   : m_columns,
                    "keys"      : m_keys,
                  ]), datafile);
}

/*
 * Function:    load_data
 * Description: Call this to load the data from a persisted file.
 */
public void
load_data()
{
    string datafile;
    mapping loaded_data;
    
    datafile = query_database_file();
    if (!strlen(datafile))
    {
        return;
    }

    // Set the id information to access the filesystem
    setuid();
    seteuid(getuid());

    // Restore the values from the file
    if (file_size(datafile + ".o") > 0)
    {
        loaded_data = restore_map(datafile);
        if (pointerp(loaded_data["rows"]))
        {    
            m_rows = loaded_data["rows"];
        }
        if (pointerp(loaded_data["columns"]))
        {
            m_columns = loaded_data["columns"];
        }
        if (pointerp(loaded_data["keys"]))
        {
            m_keys = loaded_data["keys"];
        }
    }    
}

/* 
 * Function:    create_database
 * Description: Maskable function. Use this to create the columns
 *              of a new database
 */
public void
create_database()
{
}

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
public nomask void
create()
{
    // Initialize the variables
    m_rows = ({ });
    m_columns = ({ });
    m_keys = ({ });
    
    load_data();
    
    add_column("id"); // every database has an id column
    reset_row_ids();
    create_database();
    
    save_data(); // to write out the file if it hasn't been created    
}

/*
 * Function:    add_column
 * Description: Adds a new column to the database table
 *              It also adds a column to all existing rows if it
 *              doesn't already exist
 * Arguments:   column - name of the column to add
 *              required - flag to indicate whether this column is a
 *                         required column (key)
 * Returns:     0/1 - failure/success
 */
public int
add_column(string column, int required = 0)
{
    column = lower_case(column);
    if (IN_ARRAY(column, m_columns))
    {
        // Column already added.
        return 0;
    }

    foreach (mixed row : m_rows)
    {
        if (!mappingp(row)
            || row[column])
        {
            continue;
        }

        // Set the default value of the column to 0
        row[column] = 0;
    }
    
    m_columns += ({ column });
    if (required)
    {
        m_keys += ({ column });
    }
    save_data();
    
    return 1;
}

/*
 * Function:    remove_column
 * Description: Removes a column from the database table
 *              It also loops over existing rows and removes the column
 *              from the rows.
 * Arguments:   column - name of the column to remove
 * Returns:     0/1 - failure/success
 */
public int
remove_column(string column)
{
    column = lower_case(column);
    if (!IN_ARRAY(column, m_columns))
    {
        // No such column to remove.
        return 0;
    }

    mixed * rows_to_delete = ({ });
    foreach (mixed row : m_rows)
    {
        if (!mappingp(row))
        {
            rows_to_delete += ({ row });
            continue;
        }
        
        // Remove the column from the row.
        m_delkey(row, column);
    }
    m_rows -= rows_to_delete;
    m_columns -= ({ column });
    m_keys -= ({ column });
    save_data();
    
    return 1;
}

/* 
 * Function:    add_row
 * Description: Add a new row to the database table. This does not
 *              check for uniqueness or anything.
 * Arguments:   Mapping of column/value pairs.
 * Returns:     0/1 - failure/success
 */
public int
add_row(mapping row)
{
    string * rowcolumns;
    mapping conditions;
    mixed * existing_rows;
    
    conditions = ([ ]);
    rowcolumns = m_indices(row);
    foreach (string keycolumn : m_keys)
    {
        // The added row must have all required columns at the very least
        if (!IN_ARRAY(keycolumn, rowcolumns))
        {
            return 0;
        }
        conditions[keycolumn] = row[keycolumn];
    }
    
    // Check for uniqueness. A row cannot have all the same values
    // in its key columns as another row
    existing_rows = query_rows(conditions);
    if (sizeof(existing_rows) && sizeof(m_keys))
    {
        return 0;
    }
    
    // If we got here, everything is fine. We go ahead and create
    // the new row and add it to the data structure.
    m_rows += ({ row + ([ ]) });
    reset_row_ids();       
    
    save_data();
    
    return 1;
}

public int
add_or_update_row(mapping row)
{
    mapping conditions;
    string * rowcolumns;
    mixed * existing_rows;

    if (add_row(row))
    {
        return 1;
    }
    
    // The add was not successful. We check to see if all key
    // columns are present. If so, we update the row using
    // the key columns as the condition.
    conditions = ([ ]);
    rowcolumns = m_indices(row);
    foreach (string keycolumn : m_keys)
    {
        // The added row must have all required columns at the very least
        if (!IN_ARRAY(keycolumn, rowcolumns))
        {
            return 0;
        }
        conditions[keycolumn] = row[keycolumn];
    }

    existing_rows = query_rows(conditions);
    if (!sizeof(existing_rows))
    {
        return 0;
    }
    
    foreach (mapping currentrow : existing_rows)
    {
        foreach (string column, mixed value : row)
        {
            currentrow[column] = value;
        }
    }
    
    save_data();
    
    return sizeof(existing_rows);
}

/* 
 * Function:    update_row
 * Description: Updates Rows in the database table. This does not
 *              check for uniqueness or anything.
 * Arguments:   Mapping of column/value pairs.
 *              Mapping of filter conditions
 * Returns:     number of rows updated
 */
public int
update_rows(mapping updates, mapping conditions)
{
    mixed * rows;
    
    rows = query_rows(conditions);
    foreach (mixed row : rows)
    {
        foreach (string column, mixed value : updates)
        {
            row[column] = value;
        }
    }
    
    save_data();
    
    return sizeof(rows);
}

/*
 * Function:    filter_by_and_conditions
 * Description: All conditions in the mapping are combined by
 *              AND operators and checked against each row.
 * Argument:    row - mapping of the row's values
 *              conditions - mapping of the conditions
 * Returns:     Subset of rows that match the conditions
 */
public int
filter_by_and_conditions(mapping row, mapping conditions)
{
    if (!mappingp(row))
    {
        return 0;
    }
    
    if (!m_sizeof(conditions))
    {
        // If there are no filtering conditions, then we allow
        // the row to be matched
        return 1;
    }
    
    foreach (string column, mixed condition : conditions)
    {
        mixed value;
        
        // We first check for equality. If it's equal, we
        // continue on to the next condition
        if (intp(row[column]) && intp(condition)
            && row[column] == condition)
        {
            continue;
        }
        else if (stringp(row[column]) && stringp(condition)
                 && row[column] == condition)
        {
            continue;
        }
        else
        {
            // No string or int match, we return 0 for this
            // particular row
            return 0;
        }
        /*
         * Commenting out this section as it is rather expensive
        if (stringp(condition))
        {
            if (intp(row[column])
                && parse_command(condition, ({ }), " '<' %d ", value))
            {
                if (row[column] >= value)
                {
                    return 0;
                }
                continue;
            }                
            else if (stringp(row[column])
                     && parse_command(condition, ({ }), " '<' %s ", value))
            {
                if (row[column] >= value)
                {
                    return 0;
                }
                continue;
            }
            else if (intp(row[column])
                     && parse_command(condition, ({ }), " '>' %d ", value))
            {
                if (row[column] <= value)
                {
                    return 0;
                }
                continue;
            }
            else if (stringp(row[column])
                     && parse_command(condition, ({ }), " '>' %s ", value))
            {
                if (row[column] <= value)
                {
                    return 0;
                }
                continue;
            }
        } 
        */               
    }
    
    return 1;
}

/* 
 * Function:    filter_rows
 * Description: Filter out all the rows based on the input where function.
 * 
 */
public mixed *
filter_rows(function where, mapping conditions)
{
    mixed * result_rows = ({ });
    if (!functionp(where))
    {
        return ({ });
    }
    
    // Slight optimization - If no query conditions are specified,
    // we return a copy of the entire row set.
    if (m_sizeof(conditions) == 0)
    {
        return m_rows + ({ });
    }
    
    foreach (mixed row : m_rows)
    {
        if (where(row, conditions))
        {
            result_rows += ({ row });
        }
    }
    
    return result_rows;
}

/* 
 * Function:    query_rows
 * Description: Returns a list of rows that match the passed in
 *              conditions.
 */
public mixed *
query_rows(mapping conditions)
{
    // Slight optimization - If no query conditions are specified,
    // we return a copy of the entire row set.
    if (m_sizeof(conditions) == 0)
    {
        return m_rows + ({ });
    }
        
    return filter_rows(filter_by_and_conditions, conditions);
}

/*
 * Function:    remove_row
 * Description: Remove a row based on a set of filters
 * Arguments:   conditions - mapping of columns and values to match
 * Returns:     number of rows deleted
 */
public int
remove_rows(mapping conditions)
{
    mixed * rows_to_delete = query_rows(conditions);    
    m_rows -= rows_to_delete;
    
    if (sizeof(rows_to_delete))
    {
        reset_row_ids();       
        save_data();
    }
    
    return sizeof(rows_to_delete);
}

/*
 * Function:    reset_row_ids
 * Description: Sets the row ids depending on the row position
 */
public void
reset_row_ids()
{
    int index;
    
    index = 0;
    foreach (mixed row : m_rows)
    {
        row["id"] = index++;
    }
    
    save_data();
}

/* 
 * Function:    query_num_rows
 * Description: Returns the number of rows in this database
 */
public int
query_num_rows()
{
    return sizeof(m_rows);
}

public mapping
query_row_by_id(int id)
{
    if (id < 0 || id >= sizeof(m_rows))
    {
        return 0;
    }
    
    return m_rows[id];
}

public void
remove_object()
{
    save_data();
    destruct();
}
