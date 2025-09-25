#include "hash_table.h"
typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};


struct hash_table
{ 
  entry_t buckets[17];
};


ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

//F13 ?
static void entry_destroy(entry_t *t){ //dont free t-> key since its an int not a pointer but do free value and next entry
  if (!t) return;
  entry_destroy(t->next);
  //free(t->value); //was freeing memory that was not dynamically allocated with malloc/calloc/strdup/...
  free(t);
}

  


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  for (int i = 0; i < 17; i++) {
      // Only destroy entries that were dynamically created
     /* if (ht->buckets[i].key) { //TODO it never exacutes since dummy node keys == 0 wich results in statement always result in false
          entry_destroy(&ht->buckets[i]);
          puts("tried to destroy");
        }*/


        entry_destroy(ht->buckets[i].next);  // skip dummy node
        ht->buckets[i].next = NULL;         // safety
  }
  free(ht); // free the hash_table struct itself
}

//creates a new entry with a given key, value and next pointer.
static entry_t *entry_create(int key, char *value, entry_t *next)
{
 
  entry_t *t = malloc(sizeof(entry_t));
  *t = (entry_t){.key = key, .value = value , .next = next};
  return t;
}

static entry_t *find_previous_entry_for_key(entry_t *bucket, int key) {
  entry_t *entry = bucket;

  while (true) {
    if (entry->next == NULL) {
      break;
    } else if (entry->next->key == key) {
      return entry;
    } else {
      entry = entry->next;
    }
  }

  return entry;
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  entry_t bucket = ht->buckets[key%17]; //hade bara 17 innan 
  entry_t *prev_entry = find_previous_entry_for_key(&bucket, key);

  if (prev_entry->next == NULL)
  {
    return (option_t) { .success = false };
  }
  return (option_t){.success = true, .value = prev_entry->next->value};
}
