FROM ubuntu:22.04

# Install Node.js and gcc
RUN apt-get update && apt-get install -y \
    nodejs \
    npm \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy everything
COPY . .

# Build the C compiler
RUN cd compiler && \
    gcc -o p-plus-plus main.c lex.yy.c parser.tab.c ast.c semantic.c -lm && \
    chmod +x p-plus-plus

# Install Node dependencies
RUN cd server && npm install

# Expose port
EXPOSE 3001

# Start the server
CMD ["node", "server/index.js"]