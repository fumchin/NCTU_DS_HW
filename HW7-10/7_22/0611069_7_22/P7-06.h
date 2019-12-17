/*	==================== _delete ==================== 	Deletes node from the tree and rebalances 	tree if necessary. 	   Pre    tree initialized--null tree is OK.	          dataPtr contains key of node to be deleted	   Post   node is deleted and its space recycled	          -or- if key not found, tree is unchanged 	   Return success is true if deleted; false if not found	          pointer to root*/NODE*  _delete (BST_TREE* tree,    NODE* root,                 void*     dataPtr, bool* success){// Local Definitions 	NODE* dltPtr;	NODE* exchPtr;	NODE* newRoot;	void* holdPtr;//	Statements 	if (!root)	   {	    *success = false;	    return NULL;	   } // if 		if (tree->compare(dataPtr, root->dataPtr) < 0)	     root->left  = _delete (tree,    root->left, 	                            dataPtr, success);	else if (tree->compare(dataPtr, root->dataPtr) > 0)	     root->right = _delete (tree,    root->right, 	                            dataPtr, success);	else	    // Delete node found--test for leaf node 	    {	     dltPtr = root;	     if (!root->left)	         // No left subtree 	         {	          free (root->dataPtr);       // data memory	          newRoot = root->right;	          free (dltPtr);              // BST Node	          *success = true;	          return newRoot;             // base case 	         } // if true 	     else	         if (!root->right)	             // Only left subtree 	             {	              newRoot = root->left;	              free (dltPtr);	              *success = true;	              return newRoot;         // base case 	            } // if 	         else	             // Delete Node has two subtrees 	             {	              exchPtr = root->left;	              // Find largest node on left subtree	              while (exchPtr->right)	                  exchPtr = exchPtr->right;	              // Exchange Data 	              holdPtr          = root->dataPtr;	              root->dataPtr    = exchPtr->dataPtr;	              exchPtr->dataPtr = holdPtr;	              root->left       = 	                 _delete (tree,   root->left, 	                          exchPtr->dataPtr, success);	             } // else 	    } // node found 	return root; }	// _delete 