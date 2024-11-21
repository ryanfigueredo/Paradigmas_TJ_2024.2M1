import csv

# Definindo a Classe Desenvolvedor
class Desenvolvedor:
    def __init__(self, id, nome, linguagem, experiencia):
        self.id = id
        self.nome = nome
        self.linguagem = linguagem
        self.experiencia = experiencia

    def exibir(self):
        print(f"ID: {self.id}, Nome: {self.nome}, Linguagem: {self.linguagem}, Experiência: {self.experiencia} anos")

# Funções CRUD
def adicionar_desenvolvedor(lista):
    id = len(lista) + 1
    nome = input("Digite o nome do desenvolvedor: ")
    linguagem = input("Digite a linguagem principal do desenvolvedor: ")
    experiencia = input("Digite os anos de experiência: ")

    novo_desenvolvedor = Desenvolvedor(id, nome, linguagem, experiencia)
    lista.append(novo_desenvolvedor)
    print("Desenvolvedor adicionado com sucesso!")

def listar_desenvolvedores(lista):
    if len(lista) == 0:
        print("Nenhum desenvolvedor cadastrado.")
    else:
        for desenvolvedor in lista:
            desenvolvedor.exibir()

        # Perguntar se o usuário deseja exportar para CSV
        opcao = input("\nDeseja exportar a lista de desenvolvedores para um arquivo CSV? (s/n): ")
        if opcao.lower() == 's':
            salvar_desenvolvedores(lista, 'desenvolvedores.csv')

def atualizar_desenvolvedor(lista):
    id = int(input("Digite o ID do desenvolvedor que deseja atualizar: "))

    for desenvolvedor in lista:
        if desenvolvedor.id == id:
            desenvolvedor.nome = input("Digite o novo nome do desenvolvedor: ")
            desenvolvedor.linguagem = input("Digite a nova linguagem principal do desenvolvedor: ")
            desenvolvedor.experiencia = input("Digite os novos anos de experiência: ")
            print("Desenvolvedor atualizado com sucesso!")
            return

    print("Desenvolvedor não encontrado!")

def remover_desenvolvedor(lista):
    id = int(input("Digite o ID do desenvolvedor que deseja remover: "))

    for i, desenvolvedor in enumerate(lista):
        if desenvolvedor.id == id:
            lista.pop(i)
            print("Desenvolvedor removido com sucesso!")
            return

    print("Desenvolvedor não encontrado!")

# Funções de Persistência
def salvar_desenvolvedores(lista, arquivo):
    with open(arquivo, mode='w', newline='') as f:
        escritor = csv.writer(f)
        escritor.writerow(['id', 'nome', 'linguagem', 'experiencia'])
        for desenvolvedor in lista:
            escritor.writerow([desenvolvedor.id, desenvolvedor.nome, desenvolvedor.linguagem, desenvolvedor.experiencia])
    print("Dados salvos com sucesso!")

def carregar_desenvolvedores(arquivo):
    lista = []
    try:
        with open(arquivo, mode='r') as f:
            leitor = csv.DictReader(f)
            for linha in leitor:
                desenvolvedor = Desenvolvedor(int(linha['id']), linha['nome'], linha['linguagem'], linha['experiencia'])
                lista.append(desenvolvedor)
        print("Dados carregados com sucesso!")
    except FileNotFoundError:
        print("Nenhum arquivo encontrado para carregar.")
    return lista

# Função Principal
def main():
    arquivo = 'desenvolvedores.csv'
    desenvolvedores = carregar_desenvolvedores(arquivo)

    while True:
        print("\n----- CRUD de Desenvolvedores -----")
        print("1. Adicionar Desenvolvedor")
        print("2. Listar Desenvolvedores")
        print("3. Atualizar Desenvolvedor")
        print("4. Remover Desenvolvedor")
        print("5. Sair")
        opcao = input("Escolha uma opção: ")

        if opcao == '1':
            adicionar_desenvolvedor(desenvolvedores)
        elif opcao == '2':
            listar_desenvolvedores(desenvolvedores)
        elif opcao == '3':
            atualizar_desenvolvedor(desenvolvedores)
        elif opcao == '4':
            remover_desenvolvedor(desenvolvedores)
        elif opcao == '5':
            salvar_desenvolvedores(desenvolvedores, arquivo)
            print("Saindo...")
            break
        else:
            print("Opção inválida! Tente novamente.")

# Execução
if __name__ == "__main__":
    main()
