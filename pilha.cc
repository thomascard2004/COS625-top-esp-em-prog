class PilhaInt {
private:
    // Estrutura interna para representar cada elemento da pilha (um "no" encadeado)
    struct No {
        int valor;
        No* proximo;
        
        No(int v, No* p = nullptr) {
            valor = v;
            proximo = p;
        }
    };

    No* topo_ptr; 

    // Metodo auxiliar recursivo para imprimir da base para o topo
    void imprimeInvertido(No* atual, std::ostream& o, bool& primeiro) {
        if (atual == nullptr) {
            return; // Chegamos no final (base) da pilha, hora de voltar
        }
        
        // Chamada recursiva: vai descendo ate o ultimo elemento
        imprimeInvertido(atual->proximo, o, primeiro);
        
        // Na volta da recursao, imprimimos. 
        // Se nao for o primeiro numero a ser impresso, colocamos a virgula antes
        if (!primeiro) {
            o << ", ";
        }
        
        o << atual->valor;
        primeiro = false; // Apos o primeiro numero, os proximos terao virgula
    }

public:
    // 1. Construtor sem nenhum parametro
    PilhaInt() {
        topo_ptr = nullptr; 
    }

    // Destrutor para evitar vazamento de memoria
    ~PilhaInt() {
        while (topo_ptr != nullptr) {
            No* temp = topo_ptr;
            topo_ptr = topo_ptr->proximo;
            delete temp;
        }
    }

    // 2. Operador de atribuicao
    PilhaInt& operator=(const PilhaInt& outra) {
        if (this == &outra) return *this;

        while (topo_ptr != nullptr) {
            No* temp = topo_ptr;
            topo_ptr = topo_ptr->proximo;
            delete temp;
        }

        if (outra.topo_ptr == nullptr) {
            topo_ptr = nullptr;
            return *this;
        }

        topo_ptr = new No(outra.topo_ptr->valor);
        No* atual_this = topo_ptr;
        No* atual_outra = outra.topo_ptr->proximo;

        while (atual_outra != nullptr) {
            atual_this->proximo = new No(atual_outra->valor);
            atual_this = atual_this->proximo;
            atual_outra = atual_outra->proximo;
        }

        return *this; 
    }

    // 3. Metodo empilha
    void empilha(int valor) {
        topo_ptr = new No(valor, topo_ptr);
    }

    // 4. Metodo desempilha
    int desempilha() {
        if (topo_ptr == nullptr) return 0; 

        No* no_removido = topo_ptr;               
        int valor_removido = no_removido->valor;  
        
        topo_ptr = topo_ptr->proximo;             
        delete no_removido;                       

        return valor_removido;
    }

    // 5. Metodo print atualizado para a formatacao correta
    void print(std::ostream& o) {
        if (topo_ptr == nullptr) {
            o << "[ ]"; // Se estiver vazia, imprime so os colchetes
            return;
        }

        o << "[ ";
        bool primeiro = true; // Flag para controlar a virgula
        
        // Inicia a recursao passando o topo
        imprimeInvertido(topo_ptr, o, primeiro);
        
        o << " ]"; // Fecha os colchetes, sem quebrar linha
    }

    // 6. Operador << modificado para funcionar como 'empilha'
    PilhaInt& operator<<(int valor) {
        this->empilha(valor); 
        return *this;         
    }
};
