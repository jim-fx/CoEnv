<script lang="ts">
	import { showBackground, slideAmount, slideIndex, slideTitle } from '$lib/stores';
	import { writable } from 'svelte/store';

	export let steps = 1;

	const mySlideIndex = $slideAmount;
	$slideAmount += steps;
	$: visible = $slideIndex >= mySlideIndex && $slideIndex < mySlideIndex + steps;

	export let title = '';
	const _title = writable(title);
	$: if (visible) {
		$slideTitle = $_title.replace('%I', $slideIndex);
	}

	export let background = true;
	const _background = writable(background);
	$: if (visible) {
		$showBackground = $_background;
	}
</script>

{#if visible}
	<div w-screen h-screen absolute id={'slide' + mySlideIndex}>
		<slot
			index={mySlideIndex}
			step={$slideIndex - mySlideIndex}
			background={_background}
			title={_title}
		/>
	</div>
{/if}
