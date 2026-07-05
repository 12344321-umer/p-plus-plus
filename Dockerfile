FROM ubuntu:22.04

# Install curl and gcc
RUN apt-get update && apt-get install -y \
    curl \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Install Node.js 20
RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt-get install -y nodejs

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