document.addEventListener("DOMContentLoaded", () => {
    const board = document.getElementById('board');
    const cells = document.querySelectorAll('.cell');
    const resetButton = document.getElementById('reset');
    let gameBoard = Array(9).fill(null);
    const HUMAN_PLAYER = '&#127827;'; // X 이모지
    const AI_PLAYER = '&#127819;'; // O 이모지

    const winningCombos = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6]
    ];

    cells.forEach(cell => {
        cell.addEventListener('click', handleCellClick, { once: true });
    });

    resetButton.addEventListener('click', resetGame);

    function handleCellClick(e) {
        const cell = e.target;
        const index = cell.dataset.index;

        if (!gameBoard[index]) {
            makeMove(cell, index, HUMAN_PLAYER);
            if (!checkWin(gameBoard, HUMAN_PLAYER) && !isBoardFull(gameBoard)) {
                setTimeout(() => {
                    const bestMove = getBestMove(gameBoard);
                    makeMove(cells[bestMove], bestMove, AI_PLAYER);
                }, 600);
            }
        }
    }

    function makeMove(cell, index, player) {
        gameBoard[index] = player;
        cell.innerHTML = player;
        cell.style.pointerEvents = 'none';
        if (checkWin(gameBoard, player)) {
            setTimeout(() => alert(`내가 인간을 이겼다!`), 100);
        } else if (isBoardFull(gameBoard)) {
            setTimeout(() => alert(`동점!`), 100);
        }
    }

    function checkWin(board, player) {
        return winningCombos.some(combo => {
            return combo.every(index => board[index] === player);
        });
    }

    function isBoardFull(board) {
        return board.every(cell => cell !== null);
    }

    function getBestMove(board) {
        let bestScore = -Infinity;
        let move;
        board.forEach((cell, index) => {
            if (cell === null) {
                board[index] = AI_PLAYER;
                let score = minimax(board, 0, false);
                board[index] = null;
                if (score > bestScore) {
                    bestScore = score;
                    move = index;
                }
            }
        });
        return move;
    }

    function minimax(board, depth, isMaximizing) {
        if (checkWin(board, AI_PLAYER)) {
            return 10 - depth;
        } else if (checkWin(board, HUMAN_PLAYER)) {
            return depth - 10;
        } else if (isBoardFull(board)) {
            return 0;
        }

        if (isMaximizing) {
            let bestScore = -Infinity;
            board.forEach((cell, index) => {
                if (cell === null) {
                    board[index] = AI_PLAYER;
                    let score = minimax(board, depth + 1, false);
                    board[index] = null;
                    bestScore = Math.max(score, bestScore);
                }
            });
            return bestScore;
        } else {
            let bestScore = Infinity;
            board.forEach((cell, index) => {
                if (cell === null) {
                    board[index] = HUMAN_PLAYER;
                    let score = minimax(board, depth + 1, true);
                    board[index] = null;
                    bestScore = Math.min(score, bestScore);
                }
            });
            return bestScore;
        }
    }

    function resetGame() {
        gameBoard = Array(9).fill(null);
        cells.forEach(cell => {
            cell.textContent = '';
            cell.style.pointerEvents = 'auto';
            cell.addEventListener('click', handleCellClick, { once: true });
        });
    }
});
