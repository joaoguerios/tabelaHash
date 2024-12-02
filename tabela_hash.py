# Sistema de votação com Tabela Hash

class VotingSystem:
    def __init__(self):
        self.voted_ids = {}  # Tabela hash para armazenar IDs dos eleitores que já votaram
        self.candidate_votes = {}  # Tabela hash para contar os votos dos candidatos

    def vote(self, voter_id, candidate_name):
        # Verifica se o eleitor já votou
        if voter_id in self.voted_ids:
            return "Erro: Eleitor já votou."
        
        # Registra o voto
        self.voted_ids[voter_id] = True
        if candidate_name not in self.candidate_votes:
            self.candidate_votes[candidate_name] = 0
        self.candidate_votes[candidate_name] += 1
        return f"Voto registrado para {candidate_name}!"

    def show_results(self):
        # Exibe o resultado da eleição
        if not self.candidate_votes:
            return "Nenhum voto registrado ainda."
        
        result = "Resultado da Eleição:\n"
        for candidate, votes in self.candidate_votes.items():
            result += f"{candidate}: {votes} voto(s)\n"
        return result.strip()


# Exemplo de uso
if __name__ == "__main__":
    system = VotingSystem()
    
    print(system.vote("123", "Alice"))  # Eleitor votando pela primeira vez
    print(system.vote("123", "Bob"))   # Eleitor tentando votar novamente
    print(system.vote("124", "Bob"))   # Outro eleitor votando
    print(system.vote("125", "Alice")) # Mais um eleitor votando
    print(system.show_results())       # Resultado da eleição
