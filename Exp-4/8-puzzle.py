import heapq

def print_board(board):
    for i in range(0, 9, 3):
        row = board[i:i+3]
        print(' '.join(str(x) if x != 0 else ' ' for x in row))
    print('---------')

def heuristic(board, goal):
    return sum(1 for i in range(9) if board[i] != 0 and board[i] != goal[i])

def board_to_string(board):
    return ''.join(map(str, board))

def is_solvable(board):
    inversions = 0
    for i in range(9):
        if board[i] == 0:
            continue
        for j in range(i+1, 9):
            if board[j] != 0 and board[i] > board[j]:
                inversions += 1
    return inversions % 2 == 0

def get_successors(board):
    moves = []
    zero = board.index(0)
    row, col = divmod(zero, 3)
    directions = [(-1,0), (1,0), (0,-1), (0,1)]  # up, down, left, right
    
    for dr, dc in directions:
        new_row, new_col = row + dr, col + dc
        if 0 <= new_row < 3 and 0 <= new_col < 3:
            new_zero = new_row * 3 + new_col
            new_board = board.copy()
            new_board[zero], new_board[new_zero] = new_board[new_zero], new_board[zero]
            moves.append(new_board)
    return moves

def solve_puzzle(initial, goal):
    if not is_solvable(initial):
        print("The given puzzle is not solvable.")
        return

    open_list = []
    heapq.heappush(open_list, (heuristic(initial, goal), 0, initial))
    closed_set = set()

    while open_list:
        f, g, board = heapq.heappop(open_list)

        board_str = board_to_string(board)
        if board_str in closed_set:
            continue
        closed_set.add(board_str)

        print(f"Step {g} (f = {f}):")
        print_board(board)

        if board == goal:
            print(f"Solution found in {g} moves!")
            return

        for successor in get_successors(board):
            succ_str = board_to_string(successor)
            if succ_str not in closed_set:
                h = heuristic(successor, goal)
                heapq.heappush(open_list, (g+1+h, g+1, successor))
    
    print("No solution found.")

if __name__ == "__main__":
    initial = list(map(int, input("Enter the initial state (9 numbers with 0 as blank): ").split()))
    goal = [1, 2, 3, 4, 5, 6, 7, 8, 0]
    solve_puzzle(initial, goal)
