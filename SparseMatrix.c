#include <stdio.h>

typedef struct El
{
	int row;
	int col;
	int value;
	struct El *right;
	struct El *down;
}Element;

typedef struct
{
	int number_of_rows;
	int number_of_columns;
	int number_of_nondefault_elements;

	Element* rows[100];
	Element* columns[100];
	int default_value;
}SparseMatrix;

void setDefaultValue(SparseMatrix *sparseMatrix)
{
	int value;
	printf("Insert default value:\n");
	scanf("%d", &value);
	sparseMatrix->default_value = value;
}

void Init_SparseMatrix(SparseMatrix* sparseMatrix,int number_of_rows, int number_of_columns,int default_value)
{
	setDefaultValue(sparseMatrix);
	
	sparseMatrix->number_of_nondefault_elements = 0;
	sparseMatrix->number_of_rows = number_of_rows;
	sparseMatrix->number_of_columns = number_of_columns;

	int i = 0;
	for (i = 0; i < 100; i++)
	{
		sparseMatrix->rows[i] = NULL;
		sparseMatrix->columns[i] = NULL;
	}
}

Element *getNewNode(int row,int col,int value)
{
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->col = col;
	new_element->row = row;
	new_element->value = value;
	new_element->right = NULL;
	new_element->down = NULL;

	return new_element;
}

Element *getElement(SparseMatrix *sparseMatrix,int row,int col)
{
	Element *crawler = sparseMatrix->rows[row];

	if (row > sparseMatrix->number_of_rows || col > sparseMatrix->number_of_columns)
	{
		printf("Unete vrednosti nisu u opsegu matrice! Vracen NULL");
		return NULL;
	}

	while (crawler != NULL)
	{
		if (crawler->col == col && crawler->row == row)
			return crawler;
		crawler = crawler->right;
	}
	
	return getNewNode(row, col, sparseMatrix->default_value);
}

void insertElementToRow(Element **head_ref, Element *new_element, int *is_new)
{
	Element *crawler = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_element;
		crawler = *head_ref;
	}
	else
	{
		Element *previous = crawler;
		while ((crawler != NULL) &&(new_element->col > crawler->col))
		{
			previous = crawler;
			crawler = crawler->right;
			
		}
		if (crawler != NULL && crawler->col == new_element->col && crawler->row == new_element->row)
		{
			crawler->value = new_element->value;
			*is_new = 0;
		}
		else if (crawler == NULL)
		{
			previous->right = new_element;
		}
		else
		{
			new_element->right = crawler;
			previous->right = new_element;
		}
	}
	
}

void insertElementToRowAndSum(Element **head_ref, Element *new_element, int *is_new)
{
	Element *crawler = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_element;
		crawler = *head_ref;
	}
	else
	{
		Element *previous = crawler;
		while ((crawler != NULL) && (new_element->col > crawler->col))
		{
			previous = crawler;
			crawler = crawler->right;

		}
		if (crawler != NULL && crawler->col == new_element->col && crawler->row == new_element->row)
		{
			crawler->value += new_element->value;
			*is_new = 0;
		}
		else if (crawler == NULL)
		{
			previous->right = new_element;
		}
		else
		{
			new_element->right = crawler;
			previous->right = new_element;
		}
	}

}


void deleteElementRow(Element **head_ref, Element *new_element,int *is_new)
{
	Element *crawler = *head_ref;
	if (crawler->col == new_element->col)
	{
			*head_ref = crawler->right;
			is_new = -1;
	}
	else
	{
		Element *previous = crawler;
		while ((crawler != NULL) && (new_element->col > crawler->col))
		{
			previous = crawler;
			crawler = crawler->right;
		}
		if (crawler->col == new_element->col)
		{
			previous->right = crawler->right;
			is_new = -1;
		}
	}
	
}

void deleteElementColumn(Element **head_ref, Element *new_element)
{
	Element *crawler = *head_ref;
	if (crawler->row == new_element->row)
	{
			*head_ref = crawler->down;
	}
	else
	{
		Element *previous = crawler;
		while (crawler != NULL && (new_element->row > crawler->row))
		{
			previous = crawler;
			crawler = crawler->down;
		}
		if (crawler->row == new_element->row)
		{
			previous->down = crawler->down;
			free(crawler);
		}
	}
}

void insertElementToColumn(Element **head_ref, Element *new_element)
{
	Element *crawler = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_element;
		crawler = *head_ref;
	}
	else
	{
		Element *previous = crawler;
		while ((crawler != NULL) && (new_element->row > crawler->row))
		{
			previous = crawler;
			crawler = crawler->down;

		}
		if (crawler != NULL && crawler->col == new_element->col && crawler->row == new_element->row)
		{
			crawler->value = new_element->value;
		}
		else if (crawler == NULL)
		{
			previous->down = new_element;
		}
		else
		{
			new_element->down = crawler;
			previous->down = new_element;
		}
	}
}

void insertElementToColumnAndSum(Element **head_ref, Element *new_element)
{
	Element *crawler = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_element;
		crawler = *head_ref;
	}
	else
	{
		Element *previous = crawler;
		while ((crawler != NULL) && (new_element->row > crawler->row))
		{
			previous = crawler;
			crawler = crawler->down;

		}
		if (crawler != NULL && crawler->col == new_element->col && crawler->row == new_element->row)
		{
			//Nista jer smo vec dodali
			//crawler->value += new_element->value;
		}
		else if (crawler == NULL)
		{
			previous->down = new_element;
		}
		else
		{
			new_element->down = crawler;
			previous->down = new_element;
		}
	}
}

int ElementExist(SparseMatrix* sparseMatrix, int row, int column)
{
	int n = sparseMatrix->number_of_rows;
	int i = 1;
	Element *node;
	for (i = 1; i <= n; i++)
	{
		node = sparseMatrix->rows[i];

		while (node != NULL)
		{
			if (node->row == row && node->col == column)
				return 1;
			node = node->right;
		}
	}
	return 0;
}

void insertElementToMatrix(SparseMatrix* sparseMatrix,int row, int column,int value)
{
	Element *new_element = getNewNode(row, column, value);

	int is_new = 1;

	if (new_element->value == sparseMatrix->default_value && ElementExist(sparseMatrix,row,column))
	{
		deleteElementRow(&sparseMatrix->rows[row], new_element,&is_new);
		deleteElementColumn(&sparseMatrix->columns[row], new_element);
	}
	else if (new_element->value == sparseMatrix->default_value)
	{
		return;
	}
	else
	{
		insertElementToRow(&sparseMatrix->rows[row], new_element, &is_new);
		insertElementToColumn(&sparseMatrix->columns[column], new_element);
	}	

	sparseMatrix->number_of_nondefault_elements += is_new;
}

void insertElementToMatrixAndSum(SparseMatrix* sparseMatrix, int row, int column, int value)
{
	Element *new_element = getNewNode(row, column, value);

	int is_new = 1;

	if (new_element->value == sparseMatrix->default_value)
	{
		deleteElementRow(&sparseMatrix->rows[row], new_element, &is_new);
		deleteElementColumn(&sparseMatrix->rows[row], new_element);
	}
	else
	{
		insertElementToRowAndSum(&sparseMatrix->rows[row], new_element, &is_new);
		insertElementToColumnAndSum(&sparseMatrix->columns[column], new_element);
	}
}

void printDefaultValue(int x,int val)
{
	int i = 0;
	for (i = 0; i < x; i++)
	{
		printf("%d ", val);
	}
}

void printListByRow(Element *node,int defaultValue,int numberOfColumns)
{
	int index = 1;
	while (node != NULL)
	{
		printDefaultValue((node->col) - index, defaultValue);
		index = node->col+1;
		printf("%d ", node->value);
		node = node->right;
	}
	printDefaultValue(numberOfColumns - index+1, defaultValue);
}

void printListByColumn(Element *node)
{
	while (node != NULL)
	{
		printf("%d ", node->value);
		node = node->down;
	}
}

void printMatrix(SparseMatrix *sparseMatrix)
{
	int row = sparseMatrix->number_of_rows;
	int col = sparseMatrix->number_of_columns;

	int i;
	for (i = 1; i <= row; i++)
	{
		printListByRow(sparseMatrix->rows[i],sparseMatrix->default_value,sparseMatrix->number_of_columns);
		printf("\n");
	}
}

int GetNumberOfNonDefaultElements(SparseMatrix *m)
{
	int counter = 0;
	int row = m->number_of_rows;
	for (int i = 1; i <= row; i++)
	{
		Element *node = m->rows[i];
		while (node != NULL)
		{
			counter += 1;
			node = node->right;
		}
	}
	return counter;
}

void sumOfMatrix(SparseMatrix *m1, SparseMatrix *m2, SparseMatrix *result_matrix)
{
	int row = m1->number_of_rows;

	int i = 0;

	for (i = 1; i <= row; i++)
	{
		Element *node = m1->rows[i];
		while (node != NULL)
		{
			if(!ElementExist(m2,node->row,node->col))
				node->value += m2->default_value;
			node = node->right;
		}
	}

	for (i = 1; i <= row; i++)
	{
		Element *node = m2->rows[i];
		while (node != NULL)
		{
			if(!ElementExist(m1,node->row,node->col))
				insertElementToMatrixAndSum(result_matrix, node->row, node->col, node->value + m1->default_value);
			else
				insertElementToMatrixAndSum(result_matrix, node->row, node->col, node->value);
			node = node->right;
		}
	}

}

void DeleteSparseMatrix(SparseMatrix *sparseMatrix)
{
	int row = sparseMatrix->number_of_rows;
	int i = 0;
	for (i = 1; i <= row; i++)
	{
		Element *node = sparseMatrix->rows[i];
		Element *previous = NULL;

		while (node != NULL)
		{
			previous = node;
			node = node->right;
			free(previous);
		}
	}
	int col = sparseMatrix->number_of_columns;
	for (i = 1; i <= col; i++)
	{
		sparseMatrix->columns[i] = NULL;
		sparseMatrix->rows[i] = NULL;

	}
}

void CreateSparseMatrix(SparseMatrix *sparseMatrix)
{
	int row, col;
	printf("Enter number of rows & columns:\n");
	scanf("%d %d", &row, &col);
	Init_SparseMatrix(sparseMatrix, row, col, 0);

	printf("How many elements do you want to insert?\n");
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("Enter row,column & value for element number %d\n", i);
		int r, c, value;
		scanf("%d%d%d", &r, &c, &value);
		insertElementToMatrix(sparseMatrix, r, c, value);
	}
	printf("Sparse Matrix has been created!\n");
}

Element GetMatrixElement(SparseMatrix *sparseMatrix)
{
	int row, col;
	printf("Enter row & column of element you want to get:\n");
	scanf("%d%d", &row, &col);
	if (row > sparseMatrix->number_of_rows || col < sparseMatrix->number_of_columns || row < 1 || col < 1)
	{
		printf("Not in range. Null returned!\n");
		return NULL;
	}

	Element *el = getElement(sparseMatrix, row, col);
	printf("%d", el->value);
}

int GetNumberOfElements(SparseMatrix *sparseMatrix)
{
	int num = GetNumberOfNonDefaultElements(sparseMatrix);
	printf("Number of non-default elements: %d\n",num);
	return num;
}

void SetElementMatrix(SparseMatrix *sparseMatrix)
{
	printf("Enter row, column & value of element you want to insert:\n");
	int row, col, value;
	if (row > sparseMatrix->number_of_rows || col < sparseMatrix->number_of_columns || row < 1 || col < 1)
	{
		printf("Not in range!\n");
		return;
	}
	scanf("%d%d%d", &row, &col, &value);
	insertElementToMatrix(sparseMatrix, row, col, value);
}

void MatrixSum()
{
	SparseMatrix m1;
	SparseMatrix m2;
	SparseMatrix m3;
	
	printf("Enter parameters for 1st Sparse Matrix:\n\n");
	CreateSparseMatrix(&m1);
	printf("Enter parameters for 2n Sparse Matrix:\n\n");
	CreateSparseMatrix(&m2);
	printf("Sparse Matrix 1:\n");
	printMatrix(&m1);
	printf("Sparse Matrix 2:\n");
	printMatrix(&m2);
	m3 = m1;
	m3.default_value = m1.default_value + m2.default_value;
	sumOfMatrix(&m1, &m2, &m3);

	printf("Sum is:\n");
	printMatrix(&m3);
}

void PrintMenu()
{
	printf("------------\n");
	printf("1 - Create Sparse Matrix\n");
	printf("2 - Set Default Value\n");
	printf("3 - Get Element\n");
	printf("4 - Set Element\n");
	printf("5 - Get Number Of Elements\n");
	printf("6 - Print Matrix\n");
	printf("7 - Delete Matrix\n");
	printf("8 - Sum of 2 matrices sub-program\n");

	printf("------------\n");
}

int main()
{
	SparseMatrix sparseMatrix;

	while (1)
	{
		PrintMenu();
		int operation;
		scanf("%d", &operation);

		switch (operation)
		{
		case 1:
			CreateSparseMatrix(&sparseMatrix);
			break;
		case 2:
			setDefaultValue(&sparseMatrix);
			break;
		case 3:
			GetMatrixElement(&sparseMatrix);
			break;
		case 4:
			SetElementMatrix(&sparseMatrix);
			break;
		case 5:
			GetNumberOfElements(&sparseMatrix);
			break;
		case 6:
			printMatrix(&sparseMatrix);
			break;
		case 7:
			DeleteSparseMatrix(&sparseMatrix);
			break;
		case 8:
			MatrixSum();
			break;
		default:
			printf("Please enter valid option!\n");
			break;
		}
	}

	return 0;
}
