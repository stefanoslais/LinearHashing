**Από εκφώνηση (Documentation.pdf):**
Σε C/C++, θα αναπτύξετε μια εφαρμογή με όνομα mvote, η οποία επιτρέπει σε μια δημοσκόπο (pollster) να παρακολουθεί την εξέλιξη μιας ψηφοφορίας. Το πρόγραμμα σας με την βοήθεια μιας σύνθεσης δομών θα επιτρέπει την εισαγωγή/εξαγωγή πληροφοριών και στατιστικών στοιχείων. Τα βασικά στοιχεία των εκλεκτόρων στην ψηφοφορία πρέπει να εισάγονται και να αναζητούνται σε μια δομή που έχει κόστος προσπέλασης O(1). Κάτι τέτοιο μπορείτε να το επιτύχετε με την χρήση γραμμικού κατακερματισμού (linear hashing). Επίσης, θα πρέπει να μπορείτε δυναμικά να απαντήσετε επερωτήσεις που έχουν να κάνουν με συγκεκριμένες ομάδες συμμετεχόντων, χρησιμοποιώντας μια δομή τύπου ανεστραμμένης διπλής λίστας που επιτρέπει την κατά ταχυδρομικό κωδικό παρακολούθηση της ψηφοφορίας.

**Σχετικά με το πρόγραμμα, από README.txt**
Το load limit λ ορίζεται από τον προγραμματιστή στο mvote.c:13 με #define
To initial number m of buckets ορίζεται από τον προγραμματιστή στο hash_table.h:6 με #define

Δίνεται ως έξτρα mvote εντολή η print hashtable που εκτυπώνει τα περιεχόμενα του hashtable

