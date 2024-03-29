FROM rust:latest as builder

COPY . .

# Собираем проект
RUN cargo build --release

# Копируем исполняемый файл
COPY ./target/release/hexviewer.exe .

# Устанавливаем точку входа для контейнера
ENTRYPOINT ["hexviewer.exe"]
CMD ["$@"]